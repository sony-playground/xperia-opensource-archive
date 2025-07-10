/******************************************************************************
 *                     ____                                                   *
 *                    / ___|  ___  _ __                                       *
 *                    \___ \ / _ \| '_ \| | | |                               *
 *                    ___ ) | (_) | | | | |_| |                               *
 *                    |____/ \___/|_| |_|\__, |                               *
 *                                        |___/                               *
 *                                                                            *
 ******************************************************************************
 * Copyright (c) 2016 Sony Mobile Communications Inc.                         *
 * All rights, including trade secret rights, reserved.                       *
 ******************************************************************************
 *                                                                            *
 *****************************************************************************/
#ifndef SIN_PAYLOAD_TYPES_H_
#define SIN_PAYLOAD_TYPES_H_

/*
 * SIN payloads
 */
#define SIN_PAYLOAD_TYPE__PLT_LOADER         (0x20) /* S1 Loader image */
#define SIN_PAYLOAD_TYPE__PLT_BOOT           (0x21) /* S1 Boot image */
#define SIN_PAYLOAD_TYPE__PLT_HWCONFIG       (0x22) /* Hardware configuration */
#define SIN_PAYLOAD_TYPE__PLT_RAMETS         (0x23) /* ETS */
#define SIN_PAYLOAD_TYPE__PLT_SYS_PART_IMG   (0x24) /* System partition image */
#define SIN_PAYLOAD_TYPE__PLT_INT_ELF_PART   (0x25) /* Internal ELF partition
						       image */
#define SIN_PAYLOAD_TYPE__PLT_INT_ELF_FS     (0x26) /* Internal ELF file
						       system */
#define SIN_PAYLOAD_TYPE__PLT_MMC_FLASH_DATA (0x27) /* eMMC binary data */
#define SIN_PAYLOAD_TYPE__PLT_FOTA           (0x28) /* FOTA */
#define SIN_PAYLOAD_TYPE__PLT_RAW            (0x29) /* Raw */
#define SIN_PAYLOAD_TYPE__PLT_LICKEY         (0x2A) /* OVK for Windows */
#define SIN_PAYLOAD_TYPE__PLT_UNSPECIFIED    (0xFFFFFFFF)
#endif

