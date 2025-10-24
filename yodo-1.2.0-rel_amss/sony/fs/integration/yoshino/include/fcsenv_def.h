/*
 * Copyright (C) 2016 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */

#ifndef FCSENV_DEF_H_
#define FCSENV_DEF_H_

#include <rule_types.h>

/* Defined as SERIAL_NUM in QC doc */
#define DIE_ID_ADDR 0x00786134
#define DIE_ID_LEN 4

/* Holds OEM_HW_ID + OEM_PRODUCT_ID */
/* Defined as OEM_CONFIG3 in QC doc*/
#define OEM_IDS_ADDR 0x0078604C
#define OEM_IDS_LEN 4

/* Defined as HWIO_TLMM_HW_REVISION_NUMBER_ADDR in boot_images */
#define PLATFORM_ID_ADDR 0x03998010
#define PLATFORM_ID_LEN 4

/* HWIO_QFPROM_CORR_OEM_SEC_BOOT_ROWn_LSB_ADDR(0) in  */
#define SEC_BOOT_AUTH_ADDR 0x784350
/* SOMC:s fuse config for SEC_BOOT_AUTH fuse */
#define SEC_BOOT_AUTH_MASK 0x10303030

/* Address of platform root key hash, defined as PK_HASH0_0 in QC doc */
#define PLATFORM_ROOT_KEY_HASH_ADDR	0x00786190
#define PLATFORM_ROOT_KEY_HASH_LEN	32

/* Name of frp partition */
#define FRP_PARTITION_NAME "frp"

/* Name of TA partition */
#define TA_PARTITION_NAME "TA"

/* TA block size */
#define TA_BLOCK_SIZE (128*1024)

/* Maximal data chunk size when reading from USB */
#define MAX_USB_READ (4*1024*1024)

/* Maximal data chunk size when writing to USB */
#define MAX_USB_WRITE (1 * 2014 * 1024L)

/* Maximum number of retries when doing rescan after repartitioning */
#define RESCAN_MAX_ATTEMPTS 100

/* Sysfs node for controlling the charger */
#define CHARGING_SYSFS_NODE "/sys/class/power_supply/battery/charging_enabled"
#define CHARGING_ENABLE "1"
#define CHARGING_DISABLE "0"

/* Sysfs node for controlling the usb */
#define USB_SYSFS_NODE "/sys/class/power_supply/usb/present"
#define BCD_USB "/config/usb_gadget/g1/bcdUSB"

/* The file with the battery capacity */
#define BATTERY_CAPACITY "/sys/class/power_supply/battery/capacity"

#define FLASH_MODEL "/sys/class/block/sda/device/model"
#define FLASH_REVISION  "/sys/class/block/sda/device/rev"
#define FLASH_VENDOR "/sys/class/block/sda/device/vendor"
#define FLASH_TYPE "UFS"

#define EROOT_CERT_S1_USAGE (\
	RULE_USAGE_HWCONFIG |\
	RULE_USAGE_SIMLOCK |\
	RULE_USAGE_RLOCK |\
	RULE_USAGE_FOTA)

#define EROOT_CERT_XKEYSTORE_USAGE RULE_USAGE_KEYSTORE
#define EROOT_CERT_XFL_USAGE RULE_USAGE_LOADER_KERNEL

#define BATTERY_PWSUP_NAME_UEVENT		"POWER_SUPPLY_NAME=battery"
#define BATTERY_POWER_SUPPLY_CAPACITY		"POWER_SUPPLY_CAPACITY="
#define USB_PWSUP_NAME_UEVENT			"POWER_SUPPLY_NAME=usb"
#define USB_PWSUP_PRESENT_UEVENT		"POWER_SUPPLY_PRESENT=0"

#define QSEE_LISTENER_PROP "sys.listeners.registered"

struct embed_rootcert_item *fcsenv_get_embedded_roots(size_t *number_of_roots);
void fcsenv_free_embedded_roots(
		struct embed_rootcert_item *fcsenv_get_embedded_roots);
#endif
