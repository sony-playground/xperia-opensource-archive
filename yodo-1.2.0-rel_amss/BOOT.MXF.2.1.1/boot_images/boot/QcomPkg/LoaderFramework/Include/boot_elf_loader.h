#ifndef BOOT_ELF_LOADER_H
#define BOOT_ELF_LOADER_H

/*=============================================================================

                              Boot Loader

GENERAL DESCRIPTION
  This module performs ELF image loading.

Copyright 2019-2021 by Qualcomm Technologies, Incorporated.  All Rights Reserved.
=============================================================================*/

/*===========================================================================

                           EDIT HISTORY FOR FILE

This section contains comments describing changes made to this file.
Notice that changes are listed in reverse chronological order.

when       who     what, where, why
--------   ---     ----------------------------------------------------------
01/19/21   rhy     Added BL_ERR_ELF_LOADER_INVALID_HASH_SEGMENT_SIZE
11/01/20   ds      Blacklist feature support
09/10/20   ds      added BOOT_ELF_LOADER_PROGRAM_HEADER_BUFFER_SIZE
08/06/20   ck      Moved boot_elf_loader from boot_elf_loader.c
07/31/20   ds      support getting prg hdr size
06/19/20   ck      Added BOOT_ELF_LOADER_SYNC_NONE to boot_elf_loader_sync_type
05/10/19   ep      Initial revision
============================================================================*/

/*===========================================================================

                           INCLUDE FILES
               
===========================================================================*/
#include "boot_error_if.h"
#include "boot_comdef.h"
#include "boot_framework.h"
#include "boot_loader_if.h"
#include "boot_elf_auth.h"
#include "boot_whitelist_if.h"
#include "boot_memory_mgr_if.h"
#include "boot_blacklist_if.h"

/*=============================================================================
                              DEFINITIONS
=============================================================================*/
typedef enum
{
  BL_ERR_ELF_LOADER_AUTH_FAILED                = BL_ERR_CUSTOM_ERRORS_START,
  BL_ERR_ELF_LOADER_HASH_SEGMENT_FAILURE,
  BL_ERR_ELF_LOADER_SEGMENT_OVERFLOW,
  BL_ERR_ELF_LOADER_INVALID_METADATA,
  BL_ERR_ELF_LOADER_METADATA_NOT_LOADED,
  BL_ERR_ELF_LOADER_ADDR_RANGE_OVERFLOW,
  BL_ERR_ELF_LOADER_SEGMENT_NOT_FOUND,
  BL_ERR_ELF_LOADER_INVALID_HASH_SEGMENT_SIZE

} bl_error_elf_loader_type;


typedef enum 
{
  BOOT_ELF_LOADER_ELF_HEADER_PTR              = BOOT_LOADER_NUM_ATTRIBUTES,
  BOOT_ELF_LOADER_ELF_HEADER_SIZE,
  BOOT_ELF_LOADER_ELF_FORMAT,
  BOOT_ELF_LOADER_ELF_ENTRY,  
  BOOT_ELF_LOADER_PROGRAM_HEADER_PTR,
  BOOT_ELF_LOADER_PROGRAM_HEADER_SIZE,
  BOOT_ELF_LOADER_PROGRAM_HEADER_BUFFER_SIZE,
  BOOT_ELF_LOADER_HASH_SEGMENT_BUFFER,
  BOOT_ELF_LOADER_HASH_SEGMENT_SIZE,
  BOOT_ELF_LOADER_HASH_SEGMENT_INDEX,
  BOOT_LOADER_IMAGE_ENTRY_PT_MEMORY_REGION_BASE_ADDR,
  BOOT_LOADER_IMAGE_ENTRY_PT_MEMORY_REGION_SIZE,
  BOOT_ELF_LOADER_NUM_ATTRIBUTES /* Note: this has to be last entry. Used for error checking */
} boot_elf_loader_attribute_type;


typedef enum
{
  BOOT_ELF_LOADER_SYNC_LOAD_SYNC_HASH,
  BOOT_ELF_LOADER_SYNC_LOAD_ASYNC_HASH,
  BOOT_ELF_LOADER_ASYNC_LOAD_SYNC_HASH,
  BOOT_ELF_LOADER_ASYNC_LOAD_ASYNC_HASH,
  BOOT_ELF_LOADER_SYNC_NONE
} boot_elf_loader_sync_type;


typedef struct boot_elf_loader_metadata_type
{
  void *elf_hdr;
  void *prog_hdr;
  void *hash_buffer;
} boot_elf_loader_metadata_type;


typedef struct boot_elf_loader
{
  // common for all objects
  boot_handle_common_type handle_data;

  // handle to elf_driver owned by this object
  boot_handle elf_driver_handle;

  // handle to elf_auth owned by this object
  boot_handle elf_auth_handle;

  // pointer to the emf_auth interface
  boot_loader_auth_if_type *elf_auth_if;

  // handle to whitelist object owend by this object
  boot_handle whitelist_handle;
  boot_whitelist_if_type *whitelist_if;

  boot_boolean metadata_populated;

  boot_memory_mgr_if_type *mem_if;
  
  boot_blacklist_if_type *blacklist_if;

  boot_elf_loader_sync_type sync_type;
  
  boot_boolean whitelisted_segment_loading;

} boot_elf_loader;


/*===========================================================================
                      PUBLIC FUNCTION DECLARATIONS
===========================================================================*/



/*===========================================================================
**  Function :  boot_elf_loader_get_interface
** ==========================================================================
*/
/*!
* 
* @brief
*   This function initializes a boot_loader_interface_type object 
*
* @par Dependencies
*   None 
* 
*/
bl_error_boot_type boot_elf_loader_get_interface(void *);

#endif /* BOOT_ELF_LOADER_H */

