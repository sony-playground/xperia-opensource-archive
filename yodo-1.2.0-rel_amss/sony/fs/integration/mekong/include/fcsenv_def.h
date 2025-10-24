/*
 * Copyright (C) 2016 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */

#ifndef FCSENV_DEF_H_
#define FCSENV_DEF_H_

#include <rule_types.h>

/* Defined as SERIAL_NUM in MTK doc */
#define DIE_ID_ADDR 0x10206140
#define DIE_ID_LEN 8

/* Holds OEM_HW_ID + OEM_PRODUCT_ID */
#define EFUSEC_BASE 0x10206000
#define C_DAT0 0x510
#define OEM_IDS_ADDR (EFUSEC_BASE + C_DAT0)
#define OEM_IDS_LEN 4

/* Defined as HWIO_TLMM_HW_REVISION_NUMBER_ADDR in boot_images */
#define PLATFORM_ID_ADDR 0x03998010
#define PLATFORM_ID_LEN 4

/* HWIO_QFPROM_CORR_OEM_SEC_BOOT_ROWn_LSB_ADDR(0) */
#define SEC_BOOT_AUTH_ADDR 0x00784350
/* SOMC:s fuse config for SEC_BOOT_AUTH fuse */
#define SEC_BOOT_AUTH_MASK 0x10303030

#define PLATFORM_ROOT_KEY_HASH_ADDR	0x10206090
#define PLATFORM_ROOT_KEY_HASH_LEN	32

/* Name of frp partition */
#define FRP_PARTITION_NAME "frp"

/* Name of TA partition */
#define TA_PARTITION_NAME "ta"

/* TA block size */
#define TA_BLOCK_SIZE (128*1024)

/* Maximal data chunk size when reading from USB */
#define MAX_USB_READ (32*1024)

/* Maximal data chunk size when writing to USB */
#define MAX_USB_WRITE (32 * 1024L)

/* Maximum number of retries when doing rescan after repartitioning */
#define RESCAN_MAX_ATTEMPTS 100

/* Sysfs node for controlling the charger */
#define CHARGING_SYSFS_NODE "/sys/class/power_supply/battery/present"
#define CHARGING_ENABLE "0"
#define CHARGING_DISABLE "1"

/* Sysfs node for controlling the usb */
#define USB_SYSFS_NODE "/sys/class/power_supply/usb/online"
#define BCD_USB "/sys/class/android_usb/android0/bcdUSB"

/* The file with the battery capacity */
#define BATTERY_CAPACITY "/sys/class/power_supply/battery/capacity"

#define FLASH_VENDOR "/sys/class/block/mmcblk0/device/manfid"
#define FLASH_MODEL  "/sys/class/block/mmcblk0/device/oemid"
#define FLASH_REVISION "/sys/class/block/mmcblk0/device/hwrev"
#define FLASH_TYPE "eMMC"

#define NUM_OF_RB_INDEX 0

#endif
