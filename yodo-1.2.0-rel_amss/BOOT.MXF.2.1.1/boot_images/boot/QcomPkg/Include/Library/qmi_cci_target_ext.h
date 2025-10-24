#ifndef QMI_CCI_TARGET_EXT_H
#define QMI_CCI_TARGET_EXT_H
/******************************************************************************
  @file    qmi_cci_target_ext.h
  @brief   QMI CCI OS Specific macro/types externalized to clients.

  DESCRIPTION
  QMI OS Specific types and macros required by QCCI clients.

  ---------------------------------------------------------------------------
  Copyright (c) 2010-2011 Qualcomm Technologies Incorporated. All Rights Reserved. 
  QUALCOMM Proprietary and Confidential.
  ---------------------------------------------------------------------------
*******************************************************************************/
#include "comdef.h"
#include <Library/KernelLib.h>
#include "qmi_cci_target_ext_common.h"

#ifdef __cplusplus
extern "C" {
#endif

#define QMI_CCI_OS_SIGNAL qmi_cci_os_signal_type

extern void qmi_cci_os_signal_deinit
(
  qmi_cci_os_signal_type *sig
);

extern void qmi_cci_os_signal_clear
(
  qmi_cci_os_signal_type *sig
);

extern void qmi_cci_os_signal_wait
(
  qmi_cci_os_signal_type *sig,
  unsigned int timeout_ms
);

extern void qmi_cci_os_signal_set
(
  qmi_cci_os_signal_type *sig
);

/* This is no longer used */
#define QMI_CCI_OS_SIGNAL_INIT(ptr, os_params) \
  do { \
    (ptr)->inited = TRUE;  \
    (ptr)->signal = EventInit(0,0,SCHED_EVENT_FLAG_AUTOUNSIGNAL);  \
    (ptr)->timer_inited = FALSE;  \
  }while(0)


#define QMI_CCI_OS_SIGNAL_DEINIT(ptr) qmi_cci_os_signal_deinit(ptr)

#define QMI_CCI_OS_SIGNAL_CLEAR(ptr) qmi_cci_os_signal_clear(ptr)

#define QMI_CCI_OS_SIGNAL_WAIT(ptr, timeout_ms) qmi_cci_os_signal_wait(ptr, timeout_ms)

#define QMI_CCI_OS_SIGNAL_TIMED_OUT(ptr) ((ptr)->timed_out)

#define QMI_CCI_OS_SIGNAL_SET(ptr)  qmi_cci_os_signal_set(ptr)


#ifdef __cplusplus
}
#endif

#endif
