#ifndef BOOT_ELF_AUTH_H
#define BOOT_ELF_AUTH_H

/*=============================================================================

                              Boot ELF Auth

GENERAL DESCRIPTION
  This module does the authentication for ELF image

Copyright 2019-2020 by Qualcomm Technologies, Incorporated.  All Rights Reserved.
=============================================================================*/

/*===========================================================================

                           EDIT HISTORY FOR FILE

This section contains comments describing changes made to this file.
Notice that changes are listed in reverse chronological order.

when       who     what, where, why
--------   ---     ----------------------------------------------------------
08/06/20   ck      Moved boot_elf_auth from boot_elf_auth.c
05/30/19   ep      Initial revision
============================================================================*/

/*===========================================================================

                           INCLUDE FILES
						   
===========================================================================*/
#include "boot_comdef.h"
#include "boot_loader_auth_if.h"
#include "boot_seclib_if.h" 
#include "boot_memory_mgr_if.h"
#include "boot_whitelist_if.h"


/*=============================================================================
                              DEFINITIONS
=============================================================================*/
#define MAX_IMG_BUFFERS 15


typedef struct boot_elf_auth_validate_buffer_type
{
	void *buffer;
	uint32 buffer_size;
	uint32 segment_index;

} boot_elf_auth_validate_buffer_type;


typedef struct boot_elf_auth
{
  boot_handle_common_type handle_data;
  boot_handle handle_elf_loader;
  uint32 image_id;
  boot_handle handle_whitelist;

  void *hash_buffer;
  uint32 hash_buffer_size;

  uintnt parallel_buffer_size_max;

  ALIGN(64) sec_img_auth_verified_info_s sec_img_auth_verified_info;
  sec_img_auth_whitelist_area_t white_list_area[MAX_IMG_BUFFERS];

  boot_memory_mgr_if_type *mem_if;
  boot_seclib_if_type *seclib_if;
} boot_elf_auth;


/*===========================================================================
                      PUBLIC FUNCTION DECLARATIONS
===========================================================================*/



/*===========================================================================
**  Function :  boot_elf_auth_get_interface
** ==========================================================================
*/
/*!
* 
* @brief
*   This function initializes a boot_authenticator_if_type object 
*
* @par Dependencies
*   None 
* 
*/
bl_error_boot_type boot_elf_auth_get_interface(void *);




#endif /* BOOT_ELF_AUTH_H */

