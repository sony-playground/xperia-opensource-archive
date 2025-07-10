/*
 * Copyright (C) 2020 Sony Mobile Communications Inc.
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
#define OEM_IDS_ADDR 0x00786050

/* Defined as HWIO_JTAG_ID_ADDR in boot (HALbootHWIO.h) */
#define PLATFORM_ID_ADDR 0x00786130
#define PLATFORM_ID_LEN 4

/* HWIO_QFPROM_CORR_OEM_SEC_BOOT_ROWn_LSB_ADDR(0) in boot (HALbootHWIO.h) */
#define SEC_BOOT_AUTH_ADDR 0x00784668
/* SOMC:s fuse config for SEC_BOOT_AUTH fuse */
#define SEC_BOOT_AUTH_MASK 0x00303030

/* HWIO_USB3_PRI_DSTS_ADDR from boot_images(HalusbHWIO.h), This address has stored configuration of USB. */
#define USB3_PRI_DSTS_ADDR	(0x0a60c70c)

/* Bit mask and shifter for getting USB speed */
#define USB3_PRI_DSTS_CONNECTSPD_BMSK (0x7)

/* Address of platform root key hash, defined as PK_HASH0_0 in QC doc */
#define PLATFORM_ROOT_KEY_HASH_ADDR	0x00786190
#define PLATFORM_ROOT_KEY_HASH_LEN	48

/* Name of frp partition */
#define FRP_PARTITION_NAME "frp"

/* Default sector size */
/* It has copied from sm8250_boot/boot_images/QcomPkg/Library/UfsCommonLib/ufs_core.h */
#define DEFAULT_SECTOR_SIZE 4096
#define FLASH_TYPE "UFS"

/* Length of ufs info from SCSI spec Standard INQUIRY data */
#define FLASH_VENDOR_LEN 8
#define FLASH_MODEL_LEN 16
#define FLASH_REVISION_LEN 4

#define NUM_OF_RB_INDEX 32

/* USB Connected Speed */
/* It has copied from sm8250_boot/boot_images/QcomPkg/Drivers/UsbfnDwc3Dxe/DwcCommon.h */
typedef enum _DWC_DEVICE_CONNECT_SPEED{
  DWC_HIGH_SPEED        = 0,
  DWC_FULL_SPEED        = 1,
  DWC_LOW_SPEED         = 2,
  DWC_FULL_SPEED_48     = 3,
  DWC_SUPER_SPEED       = 4,
  DWC_SUPER_SPEED_PLUS  = 5,
} DWC_DEVICE_CONNECT_SPEED;

#endif
