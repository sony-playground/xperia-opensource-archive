#ifndef BOOT_HFAT_DEV_IOCTL_CMDS_H
#define BOOT_HFAT_DEV_IOCTL_CMDS_H

/*=============================================================================

                              Boot hfat Device Ioctl Cmds

GENERAL DESCRIPTION
  header for ioctl cmds for Hfat dev.

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

//defines for Hfat dev ioctls
//hfat dev has reservation of cmd ids 151-200
typedef enum
{
  HFAT_DEV_START = 151, // replace with actual command id name when available
  HFAT_DEV_IOCTL_MAX = 200
}hfat_ioctl_cmds;

#endif /* BOOT_HFAT_DEV_IOCTL_CMDS_H */