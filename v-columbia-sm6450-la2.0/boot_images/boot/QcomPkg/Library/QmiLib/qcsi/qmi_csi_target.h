#ifndef QMI_CSI_TARGET_H
#define QMI_CSI_TARGET_H
/******************************************************************************
  @file    qmi_csi_target.h
  @brief   QuRT OS Specific routines internal to QCSI.

  DESCRIPTION
  This header provides an OS (QuRT) abstraction to QCSI.

  ---------------------------------------------------------------------------
  Copyright (c) 2012-2018 Qualcomm Technologies, Inc.  All Rights Reserved.
  Qualcomm Technologies Proprietary and Confidential.
  ---------------------------------------------------------------------------
*******************************************************************************/
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "comdef.h"
//#include "stringl.h"
#include <Library/KernelLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include "err.h"
#include "assert.h"
#include "qmi_common.h"
#include "qmi_csi_target_ext.h"
#include "qmi_idl_lib_internal.h"

#ifndef __FILENAME__
#define __FILENAME__ (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)
#endif

typedef  LockHandle* qmi_csi_lock_type;

#define LOCK(ptr)        AcquireLock(ptr)
#define UNLOCK(ptr)      ReleaseLock(ptr)
#define LOCK_INIT(ptr)   InitLock(0, ptr)
#define LOCK_DEINIT(ptr) DestroyLock(ptr)

void* qmi_csi_target_malloc(size_t size);
void *qmi_csi_target_calloc( uint32 num, size_t size );

#define MALLOC(size)      qmi_csi_target_malloc(size)
#define CALLOC(num, size) qmi_csi_target_calloc(num, size)
#define FREE(ptr)         gBS->FreePool(ptr)
//#define REALLOC(ptr,size) qmi_csi_target_realloc(ptr, size)

extern void qmi_csi_os_signal_set(qmi_csi_os_params *sig);

extern void qmi_csi_log_error(char *filename, unsigned int line);

extern void qmi_csi_os_log_tx
(
  qmi_idl_service_object_type svc_obj,
  uint32_t cntl_flag,
  uint32_t txn_id,
  uint32_t msg_id,
  uint32_t msg_len,
  void *addr,
  size_t addr_len
);

extern void qmi_csi_os_log_rx
(
  qmi_idl_service_object_type svc_obj,
  uint32_t cntl_flag,
  uint32_t txn_id,
  uint32_t msg_id,
  uint32_t msg_len,
  void *addr,
  size_t addr_len
);

extern void qmi_csi_os_log_error(char *filename, unsigned int line);

#define QMI_CSI_OS_SIGNAL_SET(s) qmi_csi_os_signal_set(s)

#define QMI_CSI_OS_LOG_TX_EXT(svc_obj, cntl_flag, txn_id, msg_id, msg_len, addr, addr_len) \
  qmi_csi_os_log_tx(svc_obj, (uint32_t)(cntl_flag), (uint32_t)(txn_id), (uint32_t)(msg_id), (uint32_t)(msg_len), addr, (size_t)(addr_len))

#define QMI_CSI_OS_LOG_RX_EXT(svc_obj, cntl_flag, txn_id, msg_id, msg_len, addr, addr_len) \
  qmi_csi_os_log_rx(svc_obj, (uint32_t)(cntl_flag), (uint32_t)(txn_id), (uint32_t)(msg_id), (uint32_t)(msg_len), addr, (size_t)(addr_len))

#define QMI_CSI_OS_LOG_ERROR() qmi_csi_os_log_error(__FILENAME__,__LINE__)

/*===========================================================================
  FUNCTION  qmi_csi_os_init
===========================================================================*/
/*!
@brief

  QCSI OS INIT function

@return
  None

@note
  None
*/
/*=========================================================================*/
void qmi_csi_os_init(void);

/*===========================================================================
  FUNCTION  qmi_csi_os_deinit
===========================================================================*/
/*!
@brief

  QCSI OS INIT function

@return
  None

@note
  None
*/
/*=========================================================================*/
void qmi_csi_os_deinit(void);

#endif
