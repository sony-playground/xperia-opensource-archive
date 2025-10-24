/*
 * Copyright (C) 2016 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */

#ifndef FCS_LOG_H_
#define FCS_LOG_H_

#include <stdlib.h>
#include "log_util.h"

void fcslog(const char *fmt, ...);
int get_fcslog(void *buf, int size);
int get_fcslog_size(void);

#ifdef CFG_ENABLE_FCS_LOG

#define FCS_LOG(fmt, args...) \
	fcslog(fmt, ##args)

#define FCS_LOG_TYPE(fmt, args...) \
	fcslog(fmt, log_util_cut_path(__BASE_FILE__), \
	__LINE__, ##args)

#ifdef CFG_ENABLE_FCS_LOG_INF
#define FCS_LOG_INF(fmt, args...) \
	FCS_LOG_TYPE("[INFO @ %s:%d]:\n" fmt, ##args)
#else
#define FCS_LOG_INF(fmt, args...) ((void)0)
#endif

#ifdef CFG_ENABLE_FCS_LOG_WRN
#define FCS_LOG_WRN(fmt, args...) \
	FCS_LOG_TYPE("[WARNING @ %s:%d]:\n" fmt, ##args)
#else
#define FCS_LOG_WRN(fmt, args...) ((void)0)
#endif

#define FCS_LOG_ERR(fmt, args...) \
	FCS_LOG_TYPE("[ERROR @ %s:%d]:\n" fmt, ##args)

#else

#define FCS_LOG(fmt, args...) ((void)0)
#define FCS_LOG_INF(fmt, args...) ((void)0)
#define FCS_LOG_WRN(fmt, args...) ((void)0)
#define FCS_LOG_ERR(fmt, args...) ((void)0)

#endif

#endif
