/** 
  @file  QcomEnvType.h
  @brief QcomEnv protocol shared structure interface.
*/
/*=============================================================================
  Copyright (c) 2020 Qualcomm Technologies, Incorporated.
  All rights reserved.
  Qualcomm Technologies, Confidential and Proprietary.
=============================================================================*/

/*=============================================================================
                              EDIT HISTORY


 when       who       what, where, why
 --------   ---       -----------------------------------------------------------
 05/27/20   yanw      init version
=============================================================================*/

#ifndef _QCOM_ENV_TYPE_H_
#define _QCOM_ENV_TYPE_H_

#include <Protocol/BlockIo.h>
#include <Protocol/DevicePath.h>


/* Selection attributes for selecting the BlkIo handles */
#define   BLK_IO_SEL_MEDIA_TYPE_REMOVABLE          0x0001UL
#define   BLK_IO_SEL_MEDIA_TYPE_NON_REMOVABLE      0x0002UL
#define   BLK_IO_SEL_PARTITIONED_GPT               0x0004UL
#define   BLK_IO_SEL_PARTITIONED_MBR               0x0008UL
#define   BLK_IO_SEL_MATCH_PARTITION_TYPE_GUID     0x0010UL
#define   BLK_IO_SEL_SELECT_MOUNTED_FILESYSTEM     0x0020UL
#define   BLK_IO_SEL_SELECT_BY_VOLUME_NAME         0x0040UL

/* Select only the root device handle indicated. Doesn't return
 * any partitions within.
 * Currently this filter applies only for eMMC device, not the external
 * device connected via USB */
#define   BLK_IO_SEL_SELECT_ROOT_DEVICE_ONLY       0x0080UL
/* Select the handle that's on the indicated root device.
 * Currently this filter applies only for eMMC device, not the external
 * device connected via USB */
#define   BLK_IO_SEL_MATCH_ROOT_DEVICE             0x0100UL

/* Select through partition name*/
#define   BLK_IO_SEL_MATCH_PARTITION_LABEL         0x0200UL

/* Do case insensetive string comparisons */
#define   BLK_IO_SEL_STRING_CASE_INSENSITIVE       0x0400UL

/* Partitioning scheme types for selecting the BlkIo handles */
#define PARTITIONED_TYPE_MBR    0x01
#define PARTITIONED_TYPE_GPT    0x02

/* Output data providing more information about the device handle */
typedef struct {
  /* Handle that has BlkIO protocol installed, returned for all type of filters */
  EFI_HANDLE                     *Handle;

  /* Block IO protocol interface is returned for all type of filters */
  EFI_BLOCK_IO_PROTOCOL          *BlkIo;

  /* This HDD dev path is returned only if Matching Partition type is requested
   * It should be noted that the contents of this memory should NOT be changed */
  const HARDDRIVE_DEVICE_PATH    *PartitionInfo;
} HandleInfo;
				 

/* Any data specific to additional attributes can be added here. */
typedef struct {
  EFI_GUID      *RootDeviceType;  /* GUID Selecting the root device type */
  EFI_GUID      *PartitionType;   /* Partition Type to match */
  CHAR8         *VolumeName;        /* Mounted filesystem volume name to match */
  CHAR16        *PartitionLabel;    /* Partition label to match */
} PartiSelectFilter;				 

#endif