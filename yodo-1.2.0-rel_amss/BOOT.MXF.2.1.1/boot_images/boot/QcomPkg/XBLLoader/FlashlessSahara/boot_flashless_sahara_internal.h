#ifndef BOOT_FLASHLESS_DEV_INTERNAL_H
#define BOOT_FLASHLESS_DEV_INTERNAL_H

/*=============================================================================

                              Boot Flashless Sahara Device (Internal)

GENERAL DESCRIPTION
  Internal header for Flashless Sahara.

Copyright 2019-2021 by Qualcomm Technologies, Incorporated.  All Rights Reserved.
=============================================================================*/

/*===========================================================================

                           EDIT HISTORY FOR FILE

This section contains comments describing changes made to this file.
Notice that changes are listed in reverse chronological order.

when       who          what, where, why
--------   ---          ----------------------------------------------------------
09/09/20   ck           Added boot statistics
10/21/19   rhythmp      Initial revision.
============================================================================*/

/*===========================================================================

                           INCLUDE FILES
               
===========================================================================*/
#include "boot_memory_mgr_if.h"
#include "boot_statistics_if.h"
#include "boot_config_context.h"
#include "boot_sahara.h"
#include "boot_sahara_internal.h"
#include "boot_framework.h"

/*=============================================================================

                              DEFINITIONS

=============================================================================*/

typedef struct boot_flashless_sahara_obj
{
  boot_handle_common_type         handle_data;
  boot_sahara_info                boot_handle_sahara_info;
  boot_memory_mgr_if_type         *mem_if;
  boot_statistics_if_type         *stats_if;
  boot_boolean                    is_last_image;
}flashless_device_handle;


#endif /* BOOT_FLASHLESS_DEV_INTERNAL_H */
