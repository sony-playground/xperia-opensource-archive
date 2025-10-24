#ifndef QMI_CCI_TARGET_H
#define QMI_CCI_TARGET_H
/******************************************************************************
  @file    qmi_cci_target.h
  @brief   OS Specific routines internal to QCCI.

  DESCRIPTION
  This header provides an OS abstraction to QCCI.

  ---------------------------------------------------------------------------
  Copyright (c) 2012 Qualcomm Technologies, Inc.  All Rights Reserved.
  Qualcomm Technologies Proprietary and Confidential.
  ---------------------------------------------------------------------------
*******************************************************************************/
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "com_dtypes.h"
#include "err.h"
#include "assert.h"
//#include "timer.h"
#include "qmi_common.h"
#include "qmi_cci_target_ext.h"
#include "qmi_idl_lib_internal.h"
#include <Library/KernelLib.h>
#include <Library/UefiBootServicesTableLib.h>

#ifndef __FILENAME__
#define __FILENAME__ (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)
#endif

typedef LockHandle* qmi_cci_lock_type;
#define LOCK(ptr)        AcquireLock(ptr)
#define UNLOCK(ptr)      ReleaseLock(ptr)
#define LOCK_INIT(ptr)   InitLock(0, ptr)
#define LOCK_DEINIT(ptr) DestroyLock(ptr)

void *qmi_cci_target_calloc( uint32 num, size_t size );
void qmi_cci_target_free( void *pMem );
void* qmi_cci_target_malloc(size_t size);

#define MALLOC_QCCI(size)      qmi_cci_target_malloc(size)
#define CALLOC_QCCI(num, size) qmi_cci_target_calloc(num, size)
#define FREE_QCCI(ptr)         qmi_cci_target_free(ptr)
//#define REALLOC(ptr,size) qmi_cci_target_realloc(ptr, size)

extern void qmi_cci_os_ext_signal_init
(
  qmi_cci_os_signal_type *sig
);

extern void qmi_cci_os_signal_init_self
(
  qmi_cci_os_signal_type *sig,
  qmi_cci_os_signal_type *os_params
);

extern void qmi_cci_os_copy_os_params
(
  qmi_cci_os_signal_type *sig,
  qmi_cci_os_signal_type *os_params
);

extern void qmi_cci_os_log_error
(
  char *filename, 
  unsigned int line
);

extern void qmi_cci_os_log_tx
(
  qmi_idl_service_object_type svc_obj,
  uint32_t cntl_flag,
  uint32_t txn_id,
  uint32_t msg_id,
  uint32_t msg_len,
  void *addr,
  size_t addr_len
);

extern void qmi_cci_os_log_rx
(
  qmi_idl_service_object_type svc_obj,
  uint32_t cntl_flag,
  uint32_t txn_id,
  uint32_t msg_id,
  uint32_t msg_len,
  void *addr,
  size_t addr_len
);

#define QMI_CCI_OS_SIGNAL_VALID(ptr) ((ptr) ? ((ptr)->inited == TRUE ? 1 : 0) : 0)
#define QMI_CCI_OS_EXT_SIGNAL_VALID(ptr) QMI_CCI_OS_SIGNAL_VALID(ptr)

#define QMI_CCI_OS_EXT_SIGNAL_INIT(ptr, os_params) \
  do {  \
    ptr = os_params;  \
    qmi_cci_os_ext_signal_init(ptr);  \
  } while(0)

#define QMI_CCI_OS_SIGNAL_INIT_SELF(ptr, os_params) qmi_cci_os_signal_init_self(ptr, os_params)

#define QMI_CCI_COPY_OS_PARAMS(ptr, src) qmi_cci_os_copy_os_params(ptr, src)

#define QMI_CCI_OS_SIGNAL_START_TIMER(ptr, timeout_ms) \
do { \
/*     if(timeout_ms && (ptr)->timer_inited) { */\
/*            timer_set_64(&((ptr)->timer), (timeout_ms), 0, T_MSEC); */\
             /* }*/ \
} while (0)

#define QMI_CCI_OS_LOG_TX_EXT(svc_obj, cntl_flag, txn_id, msg_id, msg_len, addr, addr_len) \
  qmi_cci_os_log_tx(svc_obj, (uint32_t)(cntl_flag), (uint32_t)(txn_id), (uint32_t)msg_id, (uint32_t)msg_len, addr, (size_t)addr_len)

#define QMI_CCI_OS_LOG_RX_EXT(svc_obj, cntl_flag, txn_id, msg_id, msg_len, addr, addr_len) \
  qmi_cci_os_log_rx(svc_obj, (uint32_t)(cntl_flag), (uint32_t)(txn_id), (uint32_t)msg_id, (uint32_t)msg_len, addr, (size_t)addr_len)

#define QMI_CCI_OS_LOG_ERROR() qmi_cci_os_log_error(__FILENAME__, __LINE__)

/*===========================================================================
  FUNCTION  qmi_cci_os_init
===========================================================================*/
/*!
@brief

  QCCI OS INIT function

@return
  None

@note
  None
*/
/*=========================================================================*/
void qmi_cci_os_init(void);

/*===========================================================================
  FUNCTION  qmi_cci_os_deinit
===========================================================================*/
/*!
@brief

  QCCI OS De-INIT function

@return
  None

@note
  None
*/
/*=========================================================================*/
void qmi_cci_os_deinit(void);

#endif

