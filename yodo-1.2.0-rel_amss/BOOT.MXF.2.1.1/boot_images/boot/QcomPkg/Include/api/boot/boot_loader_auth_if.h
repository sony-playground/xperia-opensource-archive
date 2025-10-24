#ifndef BOOT_AUTHENTICATOR_IF_H
#define BOOT_AUTHENTICATOR_IF_H

/*=============================================================================

                              Boot Auth IF

GENERAL DESCRIPTION
  This module defined the boot autheticator interface

Copyright 2020 by Qualcomm Technologies, Incorporated.  All Rights Reserved.
=============================================================================*/

/*===========================================================================

                           EDIT HISTORY FOR FILE

This section contains comments describing changes made to this file.
Notice that changes are listed in reverse chronological order.

when       who     what, where, why
--------   ---     ----------------------------------------------------------
11/19/20   ds      Added image_load_complete function
09/03/20   ck      Added milestone_segment_load functions
08/06/20   ck      Updated authenticate_buffer_update argument list
06/19/20   ck      Removed authenticate_buffer_update_done
============================================================================*/

/*===========================================================================

                           INCLUDE FILES
						   
===========================================================================*/
#include "boot_comdef.h"
#include "boot_error_if.h"
#include "boot_config_context.h"

/*=============================================================================

                              DEFINITIONS

=============================================================================*/


typedef struct boot_loader_auth_if_type
{  
  bl_error_boot_type (*open)(const boot_handle, const boot_handle, const boot_handle, boot_handle *);
  bl_error_boot_type (*validate_ehdr)(const boot_handle, boot_boolean *);
  bl_error_boot_type (*authenticate_metadata)(const boot_handle, boot_boolean *);
  bl_error_boot_type (*authenticate_data)(const boot_handle, boot_boolean *);
  bl_error_boot_type (*authenticate_buffer_init)(const boot_handle, void *);
  bl_error_boot_type (*authenticate_buffer_update)(const boot_handle, void *);
  bl_error_boot_type (*authenticate_buffer_finalize)(const boot_handle, void *);
  bl_error_boot_type (*milestone_segment_load_begin)(const boot_handle, uint8, uintnt, uintnt, uintnt);
  bl_error_boot_type (*milestone_segment_load_complete)(const boot_handle);
  bl_error_boot_type (*copy_verified_info)(const boot_handle, void *);
  bl_error_boot_type (*close)(const boot_handle);
  bl_error_boot_type (*image_load_complete)(const boot_handle, boot_boolean);
} boot_loader_auth_if_type;

#endif /* BOOT_AUTHENTICATOR_IF_H */

