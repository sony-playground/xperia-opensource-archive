#ifndef BOOT_PAGE_DEV_IOCTL_CMDS_H
#define BOOT_PAGE_DEV_IOCTL_CMDS_H

/*=============================================================================

                              Boot Page Device Ioctl Cmds

GENERAL DESCRIPTION
  header for ioctl cmds for page dev.

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

//defines for page dev ioctls
//page dev has reservation of cmd ids 51-100
typedef enum
{
  PDEV_IOCTL_START = 51, // replace with actual command id name when available
  PDEV_IOCTL_MAX = 100
}pdev_ioctl_cmds;

#endif /* BOOT_PAGE_DEV_IOCTL_CMDS_H */