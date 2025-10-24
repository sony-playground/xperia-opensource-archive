/*
 * Copyright (C) 2017 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */

#include "fcs_prop.h"
#include "fcserr.h"
#include "fcslog.h"

#include <sys/wait.h>
#include <unistd.h>

static int fcs_prop_ffs_ready(void)
{
	static char * const cmd[] = {
		"sh", "/etc/init.d/ffs_ready.sh", NULL};
	pid_t pid;
	int res = FCSERR_OK;
	int status;

	pid = fork();
	if (pid < 0) {
		FCS_LOG_ERR("Fork failed\n");
		res = -FCSERR_EINVAL;
		goto exit;
	} else if (pid == 0) {
		res = execvp(cmd[0], cmd);
		FCS_LOG_ERR("Failed execute ffs script\n");
		res = -FCSERR_EINVAL;
		_exit(-1);
	} else {
		if ((waitpid(pid, &status, 0) < 0) || WIFSIGNALED(status) ||
				WEXITSTATUS(status) != 0) {
			FCS_LOG_ERR("Script failed.\n");
			res = -FCSERR_EINVAL;
			goto exit;
		}
	}
exit:
	return res;
}

int fcs_prop_set(enum fcs_prop prop)
{
	switch (prop) {
	case FCS_PROP_FFS_READY:
		return fcs_prop_ffs_ready();
	case FCS_PROP_SHUTDOWN:
		break;
	case FCS_PROP_REBOOT_BOOTLOADER:
		break;
	case FCS_PROP_REBOOT_SYSTEM:
		break;
	case FCS_PROP_REBOOT_XFL:
		break;
	case FCS_PROP_START_QSEECOMD:
		break;
	case FCS_PROP_STOP_QSEECOMD:
		break;
	default:
		FCS_LOG_ERR("Invalid prop %d\n", prop);
		return -FCSERR_EINVAL;
	}

	return FCSERR_OK;
}
