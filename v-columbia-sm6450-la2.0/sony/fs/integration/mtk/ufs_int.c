/*
 * Copyright (C) 2018 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */

#include "fcslog.h"
#include "fcserr.h"
#include "ufs_int.h"

int ufs_ioctl_get_unit_desc(int fd, void *buf, size_t buf_sz)
{
	(void) fd;     /* Unused parameter */
	(void) buf;    /* Unused parameter */
	(void) buf_sz; /* Unused parameter */

	FCS_LOG_INF("MTK UFS support not implemented\n");
	return FCSERR_OK;
}

int ufs_ioctl_get_device_desc(int fd, void *buf, size_t buf_sz)
{
	(void) fd;     /* Unused parameter */
	(void) buf;    /* Unused parameter */
	(void) buf_sz; /* Unused parameter */

	FCS_LOG_INF("MTK UFS support not implemented\n");
	return FCSERR_OK;
}

int ufs_ioctl_purge(int fd)
{
	(void) fd; /* Unused parameter */

	FCS_LOG_INF("MTK UFS support not implemented\n");
	return FCSERR_OK;
}

int ufs_ioctl_set_bootdevice(int fd, int lun)
{
	(void) fd;  /* Unused parameter */
	(void) lun; /* Unused parameter */

	FCS_LOG_INF("MTK UFS support not implemented\n");
	return FCSERR_OK;
}
