#ifndef BOOT_BLACKLIST_IF_H
#define BOOT_BLACKLIST_IF_H

/*=============================================================================

                              Boot Blacklist IF

GENERAL DESCRIPTION
  Defines the Blacklist interface.

Copyright 2020 by Qualcomm Technologies, Incorporated.  All Rights Reserved.

=============================================================================*/

/*===========================================================================

                           EDIT HISTORY FOR FILE

This section contains comments describing changes made to this file.
Notice that changes are listed in reverse chronological order.

when       who          what, where, why
--------   ---          ----------------------------------------------------------
10/13/20   digants      Initial revision.
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

// blacklist interface
typedef struct boot_blacklist_if_type
{  
	bl_error_boot_type (*init)(const boot_handle);
	bl_error_boot_type (*check_region_and_update)(uintnt, uintnt);
  bl_error_boot_type (*commit_and_udpate_marker)(void);
  bl_error_boot_type (*rollback_to_last_commit)(void);
  bl_error_boot_type (*disable)(void);
  bl_error_boot_type (*enable)(void);
  bl_error_boot_type (*deinit)(void);
} boot_blacklist_if_type;

typedef enum
{
  BL_ERR_BLACKLIST_NOT_INITIALIZED     = BL_ERR_CUSTOM_ERRORS_START,
  BL_ERR_LOADING_IN_BLACKLISTED_REGION
} bl_error_boot_blacklist_type;

bl_error_boot_type boot_blacklist_get_interface(void *blacklist_if);

#endif /* BOOT_BLACKLIST_IF_H */