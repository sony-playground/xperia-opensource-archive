#ifndef BOOT_LOADER_IF_H
#define BOOT_LOADER_IF_H

/*=============================================================================

                              Boot Loader IF

GENERAL DESCRIPTION
  This module defines the loader generic interface.

Copyright 2019-2021 by Qualcomm Technologies, Incorporated.  All Rights Reserved.
=============================================================================*/

/*===========================================================================

                           EDIT HISTORY FOR FILE

This section contains comments describing changes made to this file.
Notice that changes are listed in reverse chronological order.

when       who     what, where, why
--------   ---     ----------------------------------------------------------
03/25/21   rhy     Added virtual address entry in boot_loader_segment_info_type
09/11/20   rama    Changed fill_qsee_interface_image_info arguments.
08/06/20   ck      Added file_size to boot_loader_segment_info_type
06/19/20   ck      Corrected boot_loader_segment_info_type and added loadable
04/06/19   ep      Created the file

============================================================================*/

/*===========================================================================
                           INCLUDE FILES
===========================================================================*/
#include "boot_framework.h"
#include "boot_error_if.h"
#include "boot_comdef.h"

/*=============================================================================
                              DEFINITIONS
=============================================================================*/
// Loader attributes which can be accessed using set() API
typedef enum 
{
	BOOT_LOADER_NUM_SEGMENTS = 0,
	BOOT_LOADER_SEGMENT_INFO,
	BOOT_LOADER_METADATA,
	BOOT_LOADER_NUM_ATTRIBUTES
} boot_loader_attribute_type;


// Data segment info which can get accessed using get(BOOT_LOADER_SEGMENT_INFO) API
typedef struct boot_loader_segment_info_type
{
	uintnt source_size;
	uintnt source_offset;
	uintnt dest_addr;
	uintnt dest_size;
    uintnt dest_vaddr;
	uintnt file_size;
	boot_boolean loadable;
} boot_loader_segment_info_type;


// Loader IF
typedef struct boot_loader_if_type
{
	bl_error_boot_type (*open)(const boot_handle, boot_handle *);
	bl_error_boot_type (*load_image)(const boot_handle);
	bl_error_boot_type (*set_elf_prg_hash_buffer)(const boot_handle, void *, void *, void *); // elf_hdr, prg_hdr, hash_buffer
	bl_error_boot_type (*load_metadata)(const boot_handle);
	bl_error_boot_type (*enable_whitelisted_segment_loading)(const boot_handle);
	bl_error_boot_type (*copy_vinfo)(const boot_handle, void*);
	bl_error_boot_type (*fill_qsee_interface_image_info)(const boot_handle);
	bl_error_boot_type (*load_buffer)(const boot_handle, uint32, uint32, void *);
	bl_error_boot_type (*get)(const boot_handle, uint32, void *, void *);
	bl_error_boot_type (*set)(const boot_handle, uint32, void *);
	bl_error_boot_type (*close)(const boot_handle);
} boot_loader_if_type;



bl_error_boot_type boot_load_image(const boot_handle config_context_handle);


#endif /* BOOT_LOADER_IF_H */

