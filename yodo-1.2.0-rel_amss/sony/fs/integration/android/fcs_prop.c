/*
 * Copyright (C) 2017 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */

#include "fcs_prop.h"
#include "fcslog.h"
#include "fcserr.h"
#include <string.h>

#include <cutils/properties.h>

int fcs_prop_set(enum fcs_prop prop)
{
	int ret;

	switch (prop) {
	case FCS_PROP_FFS_READY:
		ret = property_set("sys.usb.ffs.ready", "1");
		break;
	case FCS_PROP_SHUTDOWN:
		ret = property_set("sys.powerctl", "shutdown");
		break;
	case FCS_PROP_REBOOT_BOOTLOADER:
		ret = property_set("sys.powerctl", "reboot,bootloader");
		break;
	case FCS_PROP_REBOOT_SYSTEM:
		ret = property_set("sys.powerctl", "reboot,oem-4E");
		break;
	case FCS_PROP_REBOOT_XFL:
		ret = property_set("sys.powerctl", "reboot,oem-53");
		break;
	case FCS_PROP_START_QSEECOMD:
		ret = property_set("ctl.start", "qseecomd");
		break;
	case FCS_PROP_STOP_QSEECOMD:
		ret = property_set("ctl.stop", "qseecomd");
		break;
	case FCS_PROP_REBOOT_RECOVERY:
		ret = property_set("sys.powerctl", "reboot,recovery");
		break;
	case FCS_PROP_SET_SHIPMODE:
		ret = property_set("vendor.sony.xfl.setshipmode", "true");
		break;
	default:
		FCS_LOG_ERR("invalid prop %d\n", prop);
		return -FCSERR_EINVAL;
	}

	if (ret < 0) {
		FCS_LOG_ERR("property_set failed (%d)\n", ret);
		return -FCSERR_EIO;
	}
	return FCSERR_OK;
}

bool fcs_prop_get_shipmode(void){
	char value[PROPERTY_VALUE_MAX];
	if (property_get("vendor.sony.xfl.setshipmode", value, "false") > 0) {
		if (strncmp(value, "true", sizeof("true")) == 0){
			return true;
		}
	}
	return false;
}
