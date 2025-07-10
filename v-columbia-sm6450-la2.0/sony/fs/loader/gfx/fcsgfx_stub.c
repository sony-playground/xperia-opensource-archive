/*
 * Copyright (C) 2018 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */

#include <stdbool.h>
#include "fcserr.h"


int fcsgfx_init(void)
{
	return -FCSERR_ENIMP;
}

int fcsgfx_deinit(bool clear)
{
	(void)clear;
	return -FCSERR_ENIMP;
}

int fcsgfx_ready(void)
{
	return -FCSERR_ENIMP;
}

int fcsgfx_running(void)
{
	return -FCSERR_ENIMP;
}

int fcsgfx_log(char *s, bool newline)
{
	(void)s;
	(void)newline;

	return -FCSERR_ENIMP;
}
