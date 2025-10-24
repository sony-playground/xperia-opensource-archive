/*
 * Copyright (C) 2018 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */

#ifndef UFS_INT_H_
#define UFS_INT_H_

/* From JEDEC spec UFS Version 3.1 */
#define MAX_LUN_COUNT (8)//bMaxNumberLU in geometry descriptor (hardcoded here)
#define UFS_ATTR_DATA_SIZE (32)
#define DEVICE_DESCRIPTOR_LEN (0x59)
#define B_LENGTH_OFFSET (0x0)    //offset in device and unit descriptor
#define B_NUMBER_LU_OFFSET (0x6) //offset in device descriptor
#define UNIT_DESCRIPTOR_LEN (0x2D)
#define B_PROVISIONING_TYPE_OFFSET (0x17) //offset in unit descriptor

int ufs_ioctl_get_unit_desc(int fd, void *buf, size_t buf_sz);
int ufs_ioctl_get_device_desc(int fd, void *buf, size_t buf_sz);
int ufs_ioctl_purge(int fd);
int ufs_ioctl_set_bootdevice(int fd, int lun);

#endif

