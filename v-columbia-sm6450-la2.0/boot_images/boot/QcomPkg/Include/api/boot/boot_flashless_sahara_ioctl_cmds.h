#ifndef BOOT_FLASHLESS_SAHARA_IOCTL_CMDS_H
#define BOOT_FLASHLESS_SAHARA_IOCTL_CMDS_H

/*=============================================================================

                              Flasless Sahara Ioctl Cmds

GENERAL DESCRIPTION
  header for ioctl cmds for flashless sahara.

Copyright 2021 by Qualcomm Technologies, Incorporated.  All Rights Reserved.
=============================================================================*/

/*===========================================================================

                           EDIT HISTORY FOR FILE

This section contains comments describing changes made to this file.
Notice that changes are listed in reverse chronological order.

when       who          what, where, why
--------   ---          ----------------------------------------------------------
07/01/21   digants      Initial revision.
============================================================================*/

/*===========================================================================

                           INCLUDE FILES
						   
===========================================================================*/

/*=============================================================================

                              DEFINITIONS

=============================================================================*/

//defines for flashless sahara ioctls
//flashless sahara has reservation of cmd ids 101-150
typedef enum
{
  FLASHLESS_SAHARA_START = 101, // replace with actual command id name when available
  FLASHLESS_SAHARA_IOCTL_MAX = 150
}flashless_sahara_ioctl_cmds;

#endif /* BOOT_FLASHLESS_SAHARA_IOCTL_CMDS_H */