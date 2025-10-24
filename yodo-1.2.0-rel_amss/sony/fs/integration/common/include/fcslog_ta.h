/*
 * Copyright (C) 2019 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */

#ifndef FCSLOG_TA_H_
#define FCSLOG_TA_H_

#include "fcslog.h"
#include "log_util.h"

void fcslog_ta(const char *fmt, ...);
int get_fcsnvlog(void *buf, int size);
int get_fcsnvlog_size(void);

#ifdef CFG_ENABLE_FCS_LOG

#define FCS_LOG_TYPE_TA(fmt, args...) \
	fcslog_ta(fmt, log_util_cut_path(__BASE_FILE__), \
	__LINE__, ##args)

#ifdef CFG_ENABLE_FCS_LOG_INF
#define FCS_LOG_INF_TA(fmt, args...) \
	FCS_LOG_TYPE_TA("[INFO @ %s:%d]:\n" fmt, ##args)
#else
#define FCS_LOG_INF_TA(fmt, args...) ((void)0)
#endif

#ifdef CFG_ENABLE_FCS_LOG_WRN
#define FCS_LOG_WRN_TA(fmt, args...) \
	FCS_LOG_TYPE_TA("[WARNING @ %s:%d]:\n" fmt, ##args)
#else
#define FCS_LOG_WRN_TA(fmt, args...) ((void)0)
#endif

#define FCS_LOG_ERR_TA(fmt, args...) \
	FCS_LOG_TYPE_TA("[ERROR @ %s:%d]:\n" fmt, ##args)

#else

#define FCS_LOG_INF_TA(fmt, args...) ((void)0)
#define FCS_LOG_WRN_TA(fmt, args...) ((void)0)
#define FCS_LOG_ERR_TA(fmt, args...) ((void)0)

#endif

#endif
