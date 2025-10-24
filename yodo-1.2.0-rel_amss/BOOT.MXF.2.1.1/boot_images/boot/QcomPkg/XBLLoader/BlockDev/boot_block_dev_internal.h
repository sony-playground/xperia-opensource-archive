#ifndef BOOT_BLOCK_DEV_INTERNAL_H
#define BOOT_BLOCK_DEV_INTERNAL_H

/*=============================================================================

                              Boot Block Device (Internal)

GENERAL DESCRIPTION
  Internal header for block dev.

Copyright 2019 by Qualcomm Technologies, Incorporated.  All Rights Reserved.
=============================================================================*/

/*===========================================================================

                           EDIT HISTORY FOR FILE

This section contains comments describing changes made to this file.
Notice that changes are listed in reverse chronological order.

when       who          what, where, why
--------   ---          ----------------------------------------------------------
09/29/19   digants      Initial revision.
============================================================================*/

/*===========================================================================

                           INCLUDE FILES
               
===========================================================================*/

/*=============================================================================

                              DEFINITIONS

=============================================================================*/
//defines as per coldplug support
#define MAX_SECTOR_SIZE 4096
#define BLOCK_COUNT_MAX 0xFFFF

#endif /* BOOT_BLOCK_DEV_INTERNAL_H */
