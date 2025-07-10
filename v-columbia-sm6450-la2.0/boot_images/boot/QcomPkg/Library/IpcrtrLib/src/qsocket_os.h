#ifndef _IPCR_SOCKET_OS_SIG_H_
#define _IPCR_SOCKET_OS_SIG_H_
/******************************************************************************
  @file    ipcr_socket_os_sig.h
  @brief   Operating system signal abstraction

  DESCRIPTION
  This header provides an operating system abstraction to the sockets interface
  to IPC Router when a direct function call API is available.

  ---------------------------------------------------------------------------
  Copyright (c) 2014 Qualcomm Technologies, Inc.  All Rights Reserved.
  Qualcomm Technologies Proprietary and Confidential.
  ---------------------------------------------------------------------------

 *******************************************************************************/

/*===========================================================================
                      INCLUDES
===========================================================================*/
#include "comdef.h"
#include <Library/KernelLib.h>
//#include "qurt.h"
//#include "timer.h"

/*===========================================================================
                       TYPE DECLARATIONS
===========================================================================*/

typedef struct {
  Event*			signal;
//  Timer*	        timer;
  boolean           timer_inited;
} ipcr_sock_os_sig_t;

/*===========================================================================
                      MACROS AND DEFINES
===========================================================================*/

/* Signal value used for events */
#define IPCR_EVENT_SIG 0x1

/* Signal value used for timeouts */
#define IPCR_TIMER_SIG 0x2

/* Initialize a signal */
#define IPCR_OS_SIGNAL_INIT(ptr, timeout) \
  do {  \
    (ptr)->timer_inited = FALSE;  \
    (ptr)->signal = EventInit(0,0,0);	\
	/*qurt_anysignal_init(&((ptr)->signal));*/ \
    if(timeout >= 0) { \
		EventWaitTimeout ((ptr)->signal, timeout);	\
		/*if(TE_SUCCESS != timer_def_osal(&((ptr)->timer), NULL, TIMER_NATIVE_OS_SIGNAL_TYPE, &((ptr)->signal), IPCR_TIMER_SIG))*/ \
		/*(ptr)->timer = TimerInit();	*/\
        /*break;*/  \
	  /*TimerSetOneshot((ptr)->timer, timeout, &qsocket_settimeoutsignal_cb, (VOID *)ptr );	*/\
	  /*timer_set_64(&(ptr)->timer, timeout, 0, T_MSEC);*/	\
      (ptr)->timer_inited = TRUE; \
    } \
  } while(0)

/* De-initialize a signal */
#define IPCR_OS_SIGNAL_DEINIT(ptr) \
  do {  \
    if((ptr)->timer_inited == TRUE) { \
	 /* CancelTimer ((ptr)->timer);	*/\
/*      timer_clr_64(&((ptr)->timer), T_MSEC); \
      timer_undef(&((ptr)->timer)); */ \
    } \
	EventDestroy ((ptr)->signal);	\
    /*qurt_anysignal_destroy(&(ptr)->signal);*/ \
  } while(0)

/* Clear an event on a signal */
#define IPCR_OS_SIGNAL_CLEAR(ptr) \
	EventUnsignal((ptr)->signal);
    //qurt_anysignal_clear(&((ptr)->signal), IPCR_EVENT_SIG)

/* Sets an event on a signal */
#define IPCR_OS_SIGNAL_SET(ptr) \
  EventSignal((ptr)->signal,0)

/* Waits for an event on a signal */
#define IPCR_OS_SIGNAL_WAIT(ptr, timeout_ms) \
  do { \
    if(IPCR_OS_SIGNAL_TIMED_OUT(ptr)) \
      break;  \
    EventWaitTimeout ((ptr)->signal, timeout_ms);	\
	/*qurt_anysignal_wait(&((ptr)->signal), IPCR_EVENT_SIG | IPCR_TIMER_SIG); */\
  } while(0)

/* Returns true if the signal previously timed-out */
#define IPCR_OS_SIGNAL_TIMED_OUT(ptr) ((ptr)->timer_inited && EventGetSignalState((ptr)->signal) == FALSE)


#endif
