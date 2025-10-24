/*
 * Copyright (C) 2020 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */

/*
 * linux implementation of fcslog.h
 */

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdarg.h>
#include "fcserr.h"
#include "fcslog.h"
#include "ta_interface.h"
#include "fcslog_ta.h"
#include <Library/PrintLib.h>

#define MAX_NVLOG_SIZE 16000
#define MAX_DEBUG_MESSAGE_LENGTH  0x200


static void write_fastbootlog_to_nvmem(const char *buf, size_t buf_len)
{
	int res;
	int unit_size;
	int write_size;
	uint8_t *nvlog = NULL;
	unsigned int diff;

	/* Get size of unit */
	res = get_ta_unit_size(TA_MISC_PART, TA_NVLOG_UNIT, &unit_size);
	if (res != FCSERR_OK)
		return;

	nvlog = malloc(unit_size + buf_len);
	if (nvlog == NULL)
		return;

	res = read_ta(TA_MISC_PART, TA_NVLOG_UNIT, nvlog, unit_size);
	if (res != FCSERR_OK && res != -FCSERR_ENOTF)
		goto exit;

	write_size = MAX_NVLOG_SIZE;
	/* Discard oldest data and write new data at the end of the buffer */
	if (buf_len > MAX_NVLOG_SIZE) {
		diff = buf_len - MAX_NVLOG_SIZE;
		memcpy(nvlog, buf + diff, MAX_NVLOG_SIZE);
	} else if ((unit_size + buf_len) > MAX_NVLOG_SIZE) {
		diff = (unit_size + buf_len) - MAX_NVLOG_SIZE;
		memmove(nvlog, nvlog + diff, unit_size - diff);
		memcpy(nvlog + unit_size - diff, buf, buf_len);
	} else {
		memcpy(nvlog + unit_size, buf, buf_len);
		write_size = unit_size + buf_len;
	}

	(void)write_ta(TA_MISC_PART, TA_NVLOG_UNIT, nvlog, write_size);

exit:
	free(nvlog);
}

void fastbootlog_ta(const char *fmt, ...)
{
	va_list ap;

	va_start(ap, fmt);

	char *log_buf = NULL;
	uint64_t log_len;

	log_buf = malloc(MAX_DEBUG_MESSAGE_LENGTH);
	log_len =  AsciiVSPrint(log_buf, MAX_DEBUG_MESSAGE_LENGTH, fmt, ap);
	write_fastbootlog_to_nvmem(log_buf, log_len);

	free(log_buf);

	va_end(ap);
}

