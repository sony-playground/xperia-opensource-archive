/**
 @file  spcom_os_al.h
 */
/*=============================================================================
 Copyright (c) 2021 Qualcomm Technologies, Incorporated.
 All rights reserved.
 Qualcomm Technologies, Confidential and Proprietary.
 =============================================================================*/

/*=============================================================================
 EDIT HISTORY


 when       who     what, where, why
 --------   ---     -----------------------------------------------------------
 07/29/21   vp      Logging improvements
 06/15/20   vp      initial release
 =============================================================================*/

#ifndef _SPCOM_OS_AL_H_
#define _SPCOM_OS_AL_H_

#include <stdint.h>		// size_t
#include <stdarg.h>		// va_arg()
#include <stdbool.h>	// bool , true , false
#include <stdio.h>		// sprintf()
#include <string.h>		// memset()

#include "DALSys.h"		// DALSYSEventHandle
#include <errno.h>      // EFAULT
#include "com_dtypes.h"
#include "comdef.h"
#include "stddef.h"

#undef SPCOMDXE_DEBUG //define this flag to increase verbosity

#ifdef SPCOMDXE_DEBUG
#define LOGI(fmt, x...) DEBUG ((EFI_D_INFO, fmt"\n", ##x))
#define LOGD(fmt, x...) DEBUG ((EFI_D_VERBOSE, fmt"\n", ##x))
#else
#define LOGI(fmt, x...)
#define LOGD(fmt, x...)
#endif

#define LOGE(fmt, x...) DEBUG ((EFI_D_ERROR, fmt"\n", ##x))

/*
 * Polling mode is used by TZ and RPM.
 * Server might need to wait for event before connected.
 * glink handle should be updated after CONNECTED notification.
 */

struct spcom_os_mutex {
	DALSYSSyncHandle hSync;
};

struct spcom_os_event {
	void* glink_handle;
	boolean signaled_by_poll;
	DALSYSEventHandle hEvent;
};

//////////////////////////////////////////////////////

extern int spcom_os_init_event(struct spcom_os_event *event);
extern int spcom_os_set_event_glink_handle(struct spcom_os_event *event, void* glink_handle); /* the handle is updated after glink_open() */
extern int spcom_os_wait_for_event_with_timeout(struct spcom_os_event *event, size_t timeout_msec);
extern int spcom_os_wait_for_event(struct spcom_os_event *event);
extern int spcom_os_signal_event(struct spcom_os_event *event);
extern int spcom_os_reset_event(struct spcom_os_event *event);
extern boolean spcom_os_is_event_signaled(struct spcom_os_event *event);

extern void* spcom_os_malloc(size_t size);
extern void spcom_os_free(void* ptr);

extern void spcom_os_msleep(size_t msec);

extern void spcom_os_assert(boolean all_ok);

void spcom_os_al_init(void);

#endif /* _SPCOM_OS_AL_H_ */
