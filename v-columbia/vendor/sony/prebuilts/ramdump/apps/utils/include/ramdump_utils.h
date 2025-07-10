/*
 * Copyright (C) 2017 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
*/
#ifndef _RAMDUMP_UTILS_H_
#define _RAMDUMP_UTILS_H_

#define MAX_PATH_LENGTH 1024

void add_dropbox_from_uuid();

void add_rd_target();

void add_last_rdtags();

void add_events_log();

void close_temp_files(void);

void add_verity_block(void);

int add_platform_info(char *buf, int size);

#endif /* _RAMDUMP_UTILS_H_ */
