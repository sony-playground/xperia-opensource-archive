/*
 * Copyright (C) 2016 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */

#ifndef FCS_DEFINES_H_
#define FCS_DEFINES_H_

/* The idea of this header file is to include defines that are global,
 * used by more than one party (loader, boot, some tzapps etc), in order
 * to have them defined only in one place, instead of two or more.
 * Inclusion of other header files here is NOT allowed.
 */

#define BOOT_NOT_UNLOCKABLE              0
#define BOOT_UNLOCKABLE                  1
#define BOOT_UNLOCKED                    2
#define BOOT_UNLOCKABLE_SIMLOCK_LOCKED   3
#define BOOT_UNLOCKABLE_SIMLOCK_UNLOCKED 4

#define RCK_LENGTH	   16
#define RCK_H_LENGTH	   32
#define RCK_H_ASCII_LENGTH 64

/*IMEI is BCD coded, 7 bytes (8th is ignored) is 14 digits */
#define IMEI_ASCII_SIZE 14
#define IMEI_BIN_SIZE   7

struct dev_binding {
	unsigned char *die_id;
	unsigned int die_id_sz;
	unsigned char *die_id_hmac;
	unsigned int die_id_hmac_sz;
	unsigned char *imei;
	unsigned int imei_sz;
	unsigned char *imei_hmac;
	unsigned int imei_hmac_sz;
};


#endif

