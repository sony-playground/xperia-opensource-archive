#ifndef BOOT_BLOCK_DEV_IOCTL_CMDS_H
#define BOOT_BLOCK_DEV_IOCTL_CMDS_H

/*=============================================================================

                              Boot Block Device Ioctl Cmds

GENERAL DESCRIPTION
  header for ioctl cmds for block dev.

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

//defines for block dev ioctls
//blockdev has reservation of cmd ids 1-50
typedef enum
{
  BDEV_SET_HW_INIT_PARTITION = 1,
  BDEV_SET_DO_BACKGROUND_INIT,
  GET_CURRENT_PARTITION_SIZE,
  BDEV_IOCTL_MAX = 50
}bdev_ioctl_cmds;

/* Physical partition to be set to act on */
typedef enum phys_partitions
{
  BOOT_PARTITION,
  USER_PARTITION,
  ALL_PARTITIONS
}phys_partitions;

#endif /* BOOT_BLOCK_DEV_IOCTL_CMDS_H */