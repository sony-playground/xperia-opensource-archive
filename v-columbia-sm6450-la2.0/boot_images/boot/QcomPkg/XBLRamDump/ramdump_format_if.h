/** @file ramdump_format_if.h
  RAM dump format interface definition

  Copyright (c) 2021 Qualcomm Technologies, Inc. All rights reserved.

**/

/*=============================================================================
                              EDIT HISTORY

 when       who     what, where, why
 --------   ---     -----------------------------------------------------------
 02/21/21   vk      Initial revision

=============================================================================*/

#ifndef _RAMDUMP_FORMAT_IF_
#define _RAMDUMP_FORMAT_IF_

#include <boot_framework.h>
#include <boot_error_if.h>


typedef struct ramdump_format_if
{
    bl_error_boot_type (*init)   (boot_handle media_if);
    bl_error_boot_type (*open)   (boot_handle media_if_handle);
    bl_error_boot_type (*read)   (boot_handle media_if_handle, void *buffer, uintnt size);
    bl_error_boot_type (*write)  (boot_handle media_if_handle, char *filename, void *buffer, uintnt size);
    bl_error_boot_type (*close)  (boot_handle media_if_handle); 
    bl_error_boot_type (*deinit) (boot_handle media_if);
}ramdump_format_if_type;

#endif
