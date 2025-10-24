/*
 * Copyright (C) 2016 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */

/*
 * linux implementation of fcslog.h
 */

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdarg.h>
#include <time.h>
#include <pthread.h>
#include "fcserr.h"

#include "fcslog.h"
#include "input_args.h"
#include "fcsgfx.h"
#include "ta_interface.h"
#include "fcslog_ta.h"

#define MAX_NVLOG_SIZE 16000

static FILE *flog;
static bool fcslog_initialized;
static pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

static void fcslog_common(const char *fmt, va_list ap, bool log2ta);
static void write_fcslog_to_nvmem(const char *buf, size_t buf_len);

/*
 * flog is never closed. Instead it's flushed whenever written to.
 * flog will append whatever log file already exists.
 */
static void fcslog_init(void)
{
	char *path = input_args_get_log();

	(void)pthread_mutex_init(&lock, NULL);

	if (strlen(path)) {
		time_t rtime;
		struct tm *itime;

		time(&rtime);
		itime = localtime(&rtime);
		flog = fopen(path, "a+");
		fprintf(flog, "INIT: %s", asctime(itime));

		write_fcslog_to_nvmem("INIT: ", strlen("INIT: "));
		write_fcslog_to_nvmem(asctime(itime), strlen(asctime(itime)));

		(void)fflush(flog);
	}
}

static void write_fcslog_to_nvmem(const char *buf, size_t buf_len)
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

void fcslog(const char *fmt, ...)
{
	va_list ap;

	va_start(ap, fmt);

	fcslog_common(fmt, ap, true);

	va_end(ap);
}

void fcslog_ta(const char *fmt, ...)
{
	va_list ap;

	va_start(ap, fmt);

	fcslog_common(fmt, ap, false);

	va_end(ap);
}

static void fcslog_common(const char *fmt, va_list ap, bool log2ta)
{
	va_list nvap;
	char *path = input_args_get_log();
	static bool fcslog_initialized;
	size_t log_len;
	char *log_buf = NULL;

	if (!fcslog_initialized) {
		fcslog_initialized = 1;
		fcslog_init();
	}

	va_copy(nvap, ap);

	/*
	 * if a log is given then write prints to it, otherwise only use stdout.
	 */
	if (strlen(path)) {
		(void)pthread_mutex_lock(&lock);
		vfprintf(flog, fmt, ap);
		(void)fflush(flog);
		(void)pthread_mutex_unlock(&lock);
	}

	/* Write log to the display  and to a non-volitile memory*/
	log_len = vsnprintf(NULL, 0, fmt, nvap) + 1;
	if (log_len > 0) {
		log_buf = malloc(log_len);
		log_len = vsnprintf(log_buf, log_len, fmt, nvap);
		if (log2ta)
			write_fcslog_to_nvmem(log_buf, log_len);
		fcsgfx_log(log_buf, false);
	}

	/* print to stdout */
	vprintf(fmt, ap);

	va_end(nvap);
	free(log_buf);
}

int get_fcsnvlog(void *buf, int size)
{
	int res;

	if (buf == NULL || size < 1)
		return -FCSERR_EINVAL;

	res = read_ta(TA_MISC_PART, TA_NVLOG_UNIT, buf, size);
	if (res != FCSERR_OK)
		return res;

	/* Clear non-volatile log */
	delete_ta(TA_MISC_PART, TA_NVLOG_UNIT);

	return FCSERR_OK;
}

int get_fcsnvlog_size(void)
{
	int res;
	int unit_size;

	res = get_ta_unit_size(TA_MISC_PART, TA_NVLOG_UNIT, &unit_size);
	if (res != FCSERR_OK)
		return res;

	return unit_size;
}

int get_fcslog_size(void)
{
	ssize_t pos = 0;
	char *path = input_args_get_log();

	if (strlen(path)) {
		if (!fcslog_initialized) {
			fcslog_initialized = 1;
			fcslog_init();
		}
		pos = ftell(flog);
	} else {
		pos = -1;
	}

	if (pos < INT_MIN || pos > INT_MAX)
		pos = -1;

	return (int)pos;
}

int get_fcslog(void *buf, int size)
{
	int res = FCSERR_OK;
	ssize_t cur;
	char *path = input_args_get_log();

	if (buf == NULL || size < 1)
		return -FCSERR_EINVAL;

	if (strlen(path)) {
		(void)pthread_mutex_lock(&lock);
		/* save file pointer */
		cur = ftell(flog);
		if (cur < 0) {
			(void)pthread_mutex_unlock(&lock);
			return -FCSERR_EIO;
		}

		/* read size bytes from beginning */
		(void)fseek(flog, 0, SEEK_SET);
		res = fread(buf, size, 1, flog);
		if (res < 0)
			return res;

		/* restore file pointer */
		(void)fseek(flog, cur, SEEK_SET);
		(void)pthread_mutex_unlock(&lock);
	}

	return res;
}
