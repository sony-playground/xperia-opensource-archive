/*
 * Copyright (C) 2016 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */

#ifndef FCS_LOG_UTIL_H_
#define FCS_LOG_UTIL_H_

/*
 * This function returns a offset to the filename in a file path string
 * without including the path to it. The returned pointer will be the input
 * string stripped of everything up to the last '/'.
 */
const char *log_util_cut_path(const char *path);

#endif
