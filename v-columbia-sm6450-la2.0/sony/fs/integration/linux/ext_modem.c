/*
 * Copyright (C) 2018 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */

#include <ext_modem.h>
#include <linux_util.h>
#include <fcserr.h>
#include <fcslog.h>
#include <ta_interface.h>
#include <sys/mount.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

/* Max config value supported, equals to number of configs + 1 */
#define EXT_MODEM_CFG_MAX 2
#define EXT_MODEM_BOOT_TIMEOUT 30 /* allow 30s to boot & fuse modem */

#define EXT_MODEM_FWPATH "/firmware"
#define EXT_MODEM_ORG_FWPATH "/dev/block/bootdevice/by-name/modem_a"
#define EXT_MODEM_FUSE_SCRIPT "/etc/fuse_modem.sh"

int ext_modem_probe(void)
{
	struct stat pstat;
	int res;

	/* check if fuse script is available */
	res = stat(EXT_MODEM_FUSE_SCRIPT, &pstat);
	if (res)
		return 0;

	return 1;
}

int ext_modem_fuse(uint8_t config)
{
	int res;
	int res2;
	char arg[2] = {0};
	char *const cmd[] = {"sh", EXT_MODEM_FUSE_SCRIPT, arg, NULL};

	if (config > EXT_MODEM_CFG_MAX) {
		FCS_LOG_ERR("Invalid config value (%d)\n", config);
		return -FCSERR_EINVAL;
	}

	/* convert config value to ASCII */
	arg[0] = '0' + config;

	/* mount modem SW file system */
	res = mount(EXT_MODEM_ORG_FWPATH, EXT_MODEM_FWPATH, "vfat", MS_RDONLY, NULL);
	if (res) {
		/* mount error */
		FCS_LOG_ERR("Failed to mount (%d)\n", res);
		return res;
	}

	res = fcs_exec(cmd, EXT_MODEM_BOOT_TIMEOUT);
	if (res != FCSERR_OK) {
		FCS_LOG_ERR("Failed to fuse modem (%d)\n", res);
		/* try to unmount if possible */
		res2 = umount(EXT_MODEM_FWPATH);
		if (res2)
			/* Only log error, not fatal */
			FCS_LOG_ERR("Failed to umount (%d)\n", res2);
		return res;
	}

	/* ext modem was successfully fused, write config to TA */
	res = write_ta(TA_MISC_PART, TA_EXT_MODEM_FUSE_TYPE, &config, 1);
	if (res != FCSERR_OK) {
		FCS_LOG_ERR("Failed to write %d to miscTA unit %d\n",
			    config, TA_EXT_MODEM_FUSE_TYPE);
		/* try to unmount if possible */
		res2 = umount(EXT_MODEM_FWPATH);
		if (res2)
			/* Only log error, not fatal */
			FCS_LOG_ERR("Failed to umount (%d)\n", res2);
		return res;
	}

	res = umount(EXT_MODEM_FWPATH);
	if (res)
		/* Only log error, not fatal */
		FCS_LOG_ERR("Failed to umount (%d)\n", res);

	return FCSERR_OK;
}
