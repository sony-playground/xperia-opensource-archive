/*
 * Copyright (C) 2016 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */

#include "log_util.h"

/*
 * This function returns a offset to the filename in a file path string
 * without including the path to it. The returned pointer will be the input
 * string stripped of everything up to the last '/'.
 */
const char *log_util_cut_path(const char *path)
{
	const char *buf = path;
	const char *last_slash = path;

	while (*buf != '\0') {
		if ((*buf == '/' || *buf == '\\') && *(buf + 1) != '\0')
			last_slash = buf + 1;
		buf++;
	}

	return last_slash;
}
