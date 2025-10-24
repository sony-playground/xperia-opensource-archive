/*
 * Copyright (C) 2016 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */

#ifndef FCS_POWER_H_
#define FCS_POWER_H_

#include <unistd.h>

/*
 * Shutdown modes
 */
#define POWER_SHUTDOWN_ON_USB_REMOVAL	(0)
#define POWER_REBOOT_SYSTEM		(1)
#define POWER_REBOOT_XFL		(2)
#define POWER_SHUTDOWN_IMMEDIATE	(3)
#define POWER_REBOOT_FASTBOOT		(4)
#define POWER_REBOOT_RECOVERY		(5)
/*
 * Shutdown the device. mode indicates if any special actions should be taken
 * when doing the action.
 */
int power_shutdown(int mode);

/*
 * Read the battery capacity (range: 0-100)
 */
int get_battery_capacity(char *buf, ssize_t buf_sz);

#endif
