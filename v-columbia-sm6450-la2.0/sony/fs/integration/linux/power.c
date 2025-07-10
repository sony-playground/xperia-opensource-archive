/*
 * Copyright (C) 2016 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */

#include "power.h"
#include "fcserr.h"
#include "uevent_handler.h"
#include "fcs_prop.h"

int power_shutdown(int mode)
{
	int ret = FCSERR_OK;

	switch (mode) {
	case POWER_SHUTDOWN_ON_USB_REMOVAL:
		/*
		 * shutdown will be done when usb disconnect is detected
		 * in uevent thread.
		 */
		uevent_thread_join();
		break;
	case POWER_REBOOT_SYSTEM:
		ret = fcs_prop_set(FCS_PROP_REBOOT_SYSTEM);
		break;
	case POWER_REBOOT_XFL:
		ret = fcs_prop_set(FCS_PROP_REBOOT_XFL);
		break;
	case POWER_SHUTDOWN_IMMEDIATE:
		ret = fcs_prop_set(FCS_PROP_SHUTDOWN);
		break;
	case POWER_REBOOT_FASTBOOT:
		ret = fcs_prop_set(FCS_PROP_REBOOT_BOOTLOADER);
		break;
	case POWER_REBOOT_RECOVERY:
		ret = fcs_prop_set(FCS_PROP_REBOOT_RECOVERY);
		break;
	default:
		ret = -FCSERR_EINVAL;
	}

	return ret;
}
