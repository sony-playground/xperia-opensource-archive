/*
 * Copyright (C) 2018 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */

#include "protocol_util.h"
#include "fcsenv_def.h"
#include "fcslog.h"
#include "fcserr.h"
#include <string.h>
#include <errno.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int set_ship_mode(void)
{
	int fd, res = FCSERR_OK;
	ssize_t write_sz, bytes_written;

	fd = open(SHIP_MODE_SYSFS_NODE, O_WRONLY);
	if (fd < 0) {
		FCS_LOG_ERR("failed to open %s, errno = %d\n",
				SHIP_MODE_SYSFS_NODE, errno);
		return -FCSERR_EOPEN;
	}

	/* This will shut the platform down */
	write_sz = strlen(SHIP_MODE_ENABLE) + 1;
	bytes_written = write(fd, SHIP_MODE_ENABLE, write_sz);
	if (bytes_written != write_sz) {
		FCS_LOG_ERR("Failed to set ship mode\n");
		res = -FCSERR_EIO;
	}
	close(fd);

	return res;
}
