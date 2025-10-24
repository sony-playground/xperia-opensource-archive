#ifndef BOOT_MEDIA_INTERFACE_IF_H
#define BOOT_MEDIA_INTERFACE_IF_H

/*=============================================================================

                              Boot Media Interface IF
                              
GENERAL DESCRIPTION
  Defines the boot media interface.

Copyright 2019-2021 by Qualcomm Technologies, Incorporated.  All Rights Reserved.
=============================================================================*/

/*===========================================================================

                           EDIT HISTORY FOR FILE

This section contains comments describing changes made to this file.
Notice that changes are listed in reverse chronological order.

when       who          what, where, why
--------   ---          ----------------------------------------------------------
07/01/21   ds           Added Ioctl support to media lib
01/22/21   rhy          Added boot_media_booting_from_storage
09/29/19   digants      Initial revision.
============================================================================*/

/*===========================================================================

                           INCLUDE FILES
						   
===========================================================================*/
#include "boot_comdef.h"
#include "boot_error_if.h"
#include "boot_framework.h"
#include <boot_page_dev_ioctl_cmds.h>
#include <boot_block_dev_ioctl_cmds.h>
#include <boot_flashless_sahara_ioctl_cmds.h>
#include <boot_hfat_dev_ioctl_cmds.h>
/*=============================================================================

                              DEFINITIONS

=============================================================================*/

/* any media can implement this common ioctl id for a default full init */
#define DEFAULT_MEDIA_INIT 0

typedef struct boot_media_interface_if_type
{  
	bl_error_boot_type (*media_hw_init)(const boot_handle); 
	bl_error_boot_type (*media_hw_deinit)(const boot_handle);
	bl_error_boot_type (*open)(const boot_handle, boot_handle *); /* (boot_config_context, boot_media_handle) */
	bl_error_boot_type (*close)(const boot_handle); 
	bl_error_boot_type (*read)(const boot_handle, void *, uint64, uint32);
	bl_error_boot_type (*write)(const boot_handle, void *, uint64, uint32); 
	bl_error_boot_type (*async_read)(const boot_handle, void *, uint64, uint32);
	bl_error_boot_type (*async_read_poll)(const boot_handle, uint8 *);
  bl_error_boot_type (*ioctl)(uint32, void*, uintnt, void*, uintnt*); /* (boot_config_context, cmd ID, param IN, IN Size, param OUT, OUT Size) */
} boot_media_interface_if_type;

bl_error_boot_type boot_media_get_interface(const boot_handle config_context_handle, void *media_interface_if);

/*===========================================================================

**  Function :  boot_media_booting_from_storage

** ==========================================================================
*/
/*!
*
* @brief
*   This function returns TRUE if boot_device is storage.
*
* @param[in]
*   None
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
bl_error_boot_type boot_media_booting_from_storage(boot_handle, boot_boolean *);

#endif /* BOOT_MEDIA_INTERFACE_IF_H */