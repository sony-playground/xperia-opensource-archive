/*
 * Copyright (C) 2016 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */

#ifndef FCSENV_DEF_H_
#define FCSENV_DEF_H_

#include <rule_types.h>

/* Defined as SERIAL_NUM in MTK doc */
#define DIE_ID_ADDR	0x11C50140
#define DIE_ID_LEN	16

/* Address to OTP registers */
#define EFUSE_LOCK_ADDR		0x11C50028
#define EFUSE_SEC_LOCK_ADDR	0x11C50068
#define EFUSE_SEC_CTRL_ADDR	0x11C50060
#define EFUSE_SEC_MSC_ADDR	0x11C504A0
#define EFUSE_C_DAT0_ADDR	0x11C50510

/* OEM ID stored in C_DAT0 OTP register */
#define OEM_IDS_ADDR	EFUSE_C_DAT0_ADDR

/* Defined as APHW_VER(offset 0x08) */
#define VER_BASE 0x08000000
#define PLATFORM_ID_ADDR	(VER_BASE + 0x08)
#define PLATFORM_ID_LEN		4

/* Platform root key hash address in OTP */
#define PLATFORM_ROOT_KEY_HASH_ADDR	0x11c50090
#define PLATFORM_ROOT_KEY_HASH_LEN	32

/* Name of frp partition */
#define FRP_PARTITION_NAME	"frp"

/* Name of TA partition */
#define TA_PARTITION_NAME	"ta"

/* TA block size */
#define TA_BLOCK_SIZE	(128*1024)

/* Maximal data chunk size when reading from USB */
#define MAX_USB_READ	(32*1024)

/* Maximal data chunk size when writing to USB */
#define MAX_USB_WRITE	(32 * 1024L)

/* Maximum number of retries when doing rescan after repartitioning */
#define RESCAN_MAX_ATTEMPTS	300

/* Sysfs node for controlling the charger */
#define CHARGING_SYSFS_NODE	"/sys/devices/platform/charger/charge_status"
#define CHARGING_ENABLE		"1"
#define CHARGING_DISABLE	"2"

/* Sysfs node for controlling the usb */
#define USB_SYSFS_NODE	"/sys/class/power_supply/usb/online"
#define BCD_USB		"/config/usb_gadget/g1/bcdUSB"

/* The file with the battery capacity */
#define BATTERY_CAPACITY "/sys/class/power_supply/battery/capacity"

#define FLASH_VENDOR	"/sys/class/block/mmcblk0/device/manfid"
#define FLASH_MODEL	"/sys/class/block/mmcblk0/device/oemid"
#define FLASH_REVISION	"/sys/class/block/mmcblk0/device/hwrev"
#define FLASH_TYPE	"eMMC"

#define NUM_OF_RB_INDEX	0

#define BATTERY_PWSUP_NAME_UEVENT	"POWER_SUPPLY_NAME=battery"
#define BATTERY_POWER_SUPPLY_CAPACITY	"POWER_SUPPLY_CAPACITY="
#define USB_PWSUP_NAME_UEVENT		"POWER_SUPPLY_NAME=usb"
#define USB_PWSUP_PRESENT_UEVENT	"POWER_SUPPLY_ONLINE=0"

#endif
