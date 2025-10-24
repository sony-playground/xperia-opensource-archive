#ifndef _BOOT_MEDIA_INITIALIZATION_H
#define _BOOT_MEDIA_INITIALIZATION_H

/*===========================================================================

                                boot_media_init_stage_def.h
                                Header File

GENERAL DESCRIPTION
  This header file contains target specific declarations and definitions
  
Copyright 2021 by Qualcomm Technologies, Inc.  All Rights Reserved.
============================================================================*/

/*===========================================================================

                           EDIT HISTORY FOR FILE

This section contains comments describing changes made to this file.
Notice that changes are listed in reverse chronological order.

when       who          what, where, why
--------   --------     ----------------------------------------------------------
07/06/21   digants      Initial Revision
============================================================================*/

/*===========================================================================

                           INCLUDE FILES

===========================================================================*/
#include <boot_comdef.h>
#include <boot_media_types.h>
#include <boot_media_interface_if.h>
/*=============================================================================

                            DEFINITIONS

=============================================================================*/

typedef enum init_stage
{
  STAGE_1,
  STAGE_2,
  STAGE_3,
  STAGE_MAX
}init_stage;

typedef struct ioctl_params
{
  uint32 cmd;
  uintnt in_value_addr;
  uintnt in_size;
}ioctl_params;

typedef struct ioctl_cmd_set_per_stage
{
  uint32 num_cmd_entries;
  ioctl_params *ioctl_cmd_set_ptr;
}ioctl_cmd_set_per_init_stage;

typedef ioctl_cmd_set_per_init_stage init_stage_to_cmd_set_table[STAGE_MAX];

typedef struct stage_cmd_set_per_media
{
  boot_media_type media_type;
  init_stage_to_cmd_set_table *stage_cmd_set_table_ptr;
}stage_cmd_set_per_media;

bl_error_boot_type boot_process_media_init_table(const boot_handle config_context_handle, stage_cmd_set_per_media *media_init_table_ptr, uint32 num_table_entries, init_stage stage); 
#endif  /* _BOOT_MEDIA_INITIALIZATION_H */
