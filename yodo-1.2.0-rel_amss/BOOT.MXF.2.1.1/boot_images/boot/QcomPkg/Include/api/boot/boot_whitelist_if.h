#ifndef BOOT_WHITELIST_IF_H
#define BOOT_WHITELIST_IF_H

/*=============================================================================

                              Boot Whitelist IF

GENERAL DESCRIPTION
  Defines the Whitelist interface.

Copyright 2019-2020 by Qualcomm Technologies, Incorporated.  All Rights Reserved.
=============================================================================*/

/*===========================================================================

                           EDIT HISTORY FOR FILE

This section contains comments describing changes made to this file.
Notice that changes are listed in reverse chronological order.

when       who          what, where, why
--------   ---          ----------------------------------------------------------
04/02/20   ck           Changed uint64 to uintnt
02/20/20   ck           Made whitelst_tbl_entry_type arch agnostic
09/29/19   digants      Initial revision.
============================================================================*/

/*===========================================================================

                           INCLUDE FILES
						   
===========================================================================*/
#include "boot_comdef.h"
#include "boot_error_if.h"
#include "boot_framework.h"
/*=============================================================================

                              DEFINITIONS

=============================================================================*/

// whitelist entry object
typedef struct whitelst_tbl_entry 
{ 
  uintnt start_addr;
  uintnt size;
} whitelst_tbl_entry_type;

// whitelist interface
typedef struct boot_whitelist_if_type
{  
	bl_error_boot_type (*open)(const boot_handle, boot_handle *, whitelst_tbl_entry_type *, uint32);
	bl_error_boot_type (*check_region)(const boot_handle, uintnt, uintnt);
	bl_error_boot_type (*get_whitelist)(const boot_handle, whitelst_tbl_entry_type *);
	bl_error_boot_type (*get_size)(const boot_handle, uintnt *);
	bl_error_boot_type (*close)(const boot_handle);
} boot_whitelist_if_type;

typedef enum
{
  BL_ERR_INVALID_ENTRY								= BL_ERR_CUSTOM_ERRORS_START,
  BL_ERR_NOT_IN_WHITELIST
} bl_error_boot_whitelist_type;

bl_error_boot_type boot_whitelist_get_interface(void *whitelist_if);

#endif /* BOOT_WHITELIST_IF_H */