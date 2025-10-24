/*
 * Copyright (C) 2017 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */

#ifndef FCS_PROP_H_
#define FCS_PROP_H_

#include <stdbool.h>

enum fcs_prop {
	FCS_PROP_FFS_READY,
	FCS_PROP_SHUTDOWN,
	FCS_PROP_REBOOT_BOOTLOADER,
	FCS_PROP_REBOOT_SYSTEM,
	FCS_PROP_REBOOT_XFL,
	FCS_PROP_START_QSEECOMD,
	FCS_PROP_STOP_QSEECOMD,
	FCS_PROP_REBOOT_RECOVERY,
	FCS_PROP_SET_SHIPMODE
};

int fcs_prop_set(enum fcs_prop prop);
bool fcs_prop_get_shipmode(void);

#endif /* FCS_PROP_H_ */
