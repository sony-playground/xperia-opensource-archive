#ifndef BOOT_EFS_IF_H
#define BOOT_EFS_IF_H
/*===========================================================================

                    BOOT EFS COOKIE IF DEFINITIONS

DESCRIPTION
  Contains wrapper definition for external efs cookie drivers

INITIALIZATION AND SEQUENCING REQUIREMENTS
  None
  
Copyright 2019-2020 by Qualcomm Technologies Incorporated.  All Rights Reserved.
============================================================================*/
/*===========================================================================

                      EDIT HISTORY FOR FILE

This section contains comments describing changes made to this file.
Notice that changes are listed in reverse chronological order.
    
    
when       who     what, where, why
--------   ---     ----------------------------------------------------------
04/16/20   rhy     Adding fs public API
08/06/19   ep      Initial Creation.

===========================================================================*/

/*==========================================================================

                               INCLUDE FILES

===========================================================================*/
#include "boot_error_if.h"
#include "fs_public.h"


typedef struct boot_efs_if_type
{
  void (*handle_cookies)(void);
  int  (*read_only_initialize)(void);
  int  (*boot_efs_stat)(const char *path, struct fs_stat *buf);
  int  (*boot_efs_get)(const char *path, void *data, fs_size_t length);
    
} boot_efs_if_type;

extern boot_efs_if_type efs_if;


#endif /* BOOT_EFS_IF_H */
