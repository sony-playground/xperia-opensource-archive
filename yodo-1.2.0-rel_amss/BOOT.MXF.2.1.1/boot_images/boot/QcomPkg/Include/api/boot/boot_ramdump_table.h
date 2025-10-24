#ifndef BOOT_RAMDUMP_TABLE_H
#define BOOT_RAMDUMP_TABLE_H

/*=============================================================================

                         SBL1 Hardware Initialization

GENERAL DESCRIPTION
  This module defines the memory debug information to be sent to host

Copyright 2010-2021, 2022 by Qualcomm Technologies Inc.  All Rights Reserved.
=============================================================================*/

/*=============================================================================

                            EDIT HISTORY FOR MODULE

This section contains comments describing changes made to the module.
Notice that changes are listed in reverse chronological order.

$Header: //components/rel/core.boot/6.1.1/QcomPkg/Include/api/boot/boot_ramdump_table.h#1 $

when       who       what, where, why
--------   ---       ----------------------------------------------------------
06/28/22   batta     Added addr parameter to ramdump_table_add_restricted_region API
02/10/21   vk        Add restricted region
02/05/21   rhy       Added ramdump_table_target_unrecoverable_error_handler
08/18/20   rhy       Initial revision
=============================================================================*/

/*=============================================================================

                            INCLUDE FILES FOR MODULE

=============================================================================*/
#include "boot_comdef.h"
#include "boot_framework.h"
#include "boot_error_if.h"

#define DLOAD_DEBUG_STRLEN_BYTES    20

typedef struct
{
    uintnt region_base;
    uintnt region_size;
    char*  desc;
    char*  filename;
}ramdump_table_memory_region;

typedef enum
{
    RAMDUMP_TABLE_OPTIONAL_DEF_NO_SAVE = 0,     /* optional, but do not save by default */
    RAMDUMP_TABLE_OPTIONAL_DEF_SAVE,            /* optional, but save by default */
    RAMDUMP_TABLE_MANDATORY                     /* mandatory, no user modification */
} ramdump_table_save_pref_type;

/*===========================================================================

                      PUBLIC FUNCTION DECLARATIONS

===========================================================================*/

/*===========================================================================

**  Function :  ramdump_table_target_get_entries_count

** ==========================================================================
*/
/*!
*
* @brief
*   This function return the number of entries in ramdump for the specific target.
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
bl_error_boot_type ramdump_table_target_get_entries_count(uint32 *);

/*===========================================================================

**  Function :  ramdump_table_target_init

** ==========================================================================
*/
/*!
*
* @brief
*   This function initializes dload_debug_info[] for the specific target.
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
bl_error_boot_type ramdump_table_target_init(boot_handle, boot_handle, boot_handle*);

/*===========================================================================

**  Function :  ramdump_table_target_deinit

** ==========================================================================
*/
/*!
*
* @brief
*   This function initializes clocks as needed for this target, as well as sets
*   up the memory regions to be used.
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
bl_error_boot_type ramdump_table_target_deinit(boot_handle, boot_handle);

/*===========================================================================

**  Function :  ramdump_table_target_unrecoverable_error_handler

** ==========================================================================
*/
/*!
*
* @brief
*   Function to handle unexpected error during RAMDUMP collection
*
* @par Dependencies
*   None
*
* @retval
*   bl_error_boot_type
*
* @par Side Effects
*   None
*
*/
bl_error_boot_type ramdump_table_target_unrecoverable_error_handler(void);

/*===========================================================================

FUNCTION ramdump_table_add_entry

DESCRIPTION
  This function adds a region to ramdump_table_info[]

DEPENDENCIES
  None.

RETURN VALUE
  BL_ERR_NONE on success.

SIDE EFFECTS
  None.

===========================================================================*/
bl_error_boot_type ramdump_table_add_entry(boot_handle ramdump_table_handle, ramdump_table_save_pref_type, uintnt mem_base, uintnt length, char *desc, char *filename);

/*===========================================================================

FUNCTION ramdump_table_add_entry

DESCRIPTION
  This function adds a region to ramdump_table_info[]

DEPENDENCIES
  None.

RETURN VALUE
  BL_ERR_NONE on success..

SIDE EFFECTS
  None.

===========================================================================*/
bl_error_boot_type ramdump_table_add_entry(boot_handle ramdump_table_handle, ramdump_table_save_pref_type, uintnt mem_base, uintnt length, char *desc, char *filename);

/*===========================================================================

FUNCTION ramdump_table_add_restricted_region

DESCRIPTION
  This function adds a restricted region to ramdump_table

DEPENDENCIES
  None.

RETURN VALUE
  BL_ERR_NONE on success.

SIDE EFFECTS
  None.

===========================================================================*/

bl_error_boot_type ramdump_table_add_restricted_region ( boot_handle ramdump_table_handle, uint64 addr, uint64 length, char *desc, char *filename, void *handler);

#endif /* BOOT_RAMDUMP_TABLE_H */
