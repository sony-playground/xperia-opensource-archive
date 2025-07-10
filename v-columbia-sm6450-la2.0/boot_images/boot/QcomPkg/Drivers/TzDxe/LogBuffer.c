/** @file  
               LogBuffer.c

GENERAL DESCRIPTION
  This file sets up log buffer and display the content in log buffer
   
  Copyright (c) 2019 - 2020 Copyright Qualcomm Technologies, Inc.  All Rights Reserved.
  Qualcomm Technologies Proprietary and Confidential.

*/
/*===========================================================================
                             EDIT HISTORY
  This section contains comments describing changes made to the module.
  Notice that changes are listed in reverse chronological order.



 when       who      what, where, why
 --------   ---      ------------------------------------------------------
 10/26/20   shl      Changed to 64 bit to align with TZ syscall structures
 06/25/20   pr       Allocated uncached memory for Embedded app names and 
                     fixed tz diag version
 06/08/20   shl      Added support for 32 bit target, some code reorg
 05/14/20   pr       Changes to adopt new Qsee diag version structure
 07/18/19   shl      Fixed some memory leak issue and memory dang issue
                     reorg the code so it will do better management   
 09/11/18   dp       Allocating buffer pool from ShmBridge for log
 02/08/18   shl      Initial version

===========================================================================*/

#include <Library/BaseMemoryLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/UncachedMemoryAllocationLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/SerialPortLib.h>
#include <Library/DebugLib.h>
#include <Protocol/EFIScm.h>
#include <Protocol/EFIShmBridge.h>
#include <Include/scm_qsee_interface.h>
#include <Include/scm_sip_interface.h>
#include "LogBuffer.h"
#include "QcomLib.h"


VOID *log_buffer = NULL;

EFI_SHMBRIDGE_PROTOCOL  *ShmBridgeProtocol = NULL;

EFI_EVENT  ExitBootServicesQseeLogEvent;
UINT32     TzDiagVersion = 0;

VOID EFIAPI ExitBootQseeLogHandler(
  IN EFI_EVENT  Event,
  IN VOID      *Context
);

/*Adding syscall to get TZ version number
 * WIll send a syscall to TZ and find out the current TZ version number.
 * Tz1.3 will return an error as this functionality is not implemented
 */

EFI_STATUS
TzGetDiagVersion (void)
{
  EFI_STATUS                Status = EFI_SUCCESS;
  UINT64                    Parameters[SCM_MAX_NUM_PARAMETERS] = {0};
  UINT64                    Results[SCM_MAX_NUM_RESULTS] = {0};
  tz_feature_version_req_t *SysCallReq = (tz_feature_version_req_t*)Parameters;
  tz_feature_version_rsp_t *SysCallRsp = (tz_feature_version_rsp_t*)Results;
  QCOM_SCM_PROTOCOL         *QcomScmProtocol = NULL;

  SysCallReq->feature_id = TZ_FVER_DIAG;

  Status = gBS->LocateProtocol (&gQcomScmProtocolGuid, NULL, (VOID**)&QcomScmProtocol);
  if (Status != EFI_SUCCESS)
  {
    return Status;
  }

  /* Make a SCM Sys call */
  Status = QcomScmProtocol->ScmSipSysCall( QcomScmProtocol,
                                           TZ_INFO_GET_FEATURE_VERSION_ID,
                                           TZ_INFO_GET_FEATURE_VERSION_ID_PARAM_ID,
                                           Parameters,
                                           Results );
  if (EFI_ERROR (Status)) 
  {
    DEBUG(( EFI_D_ERROR, "ScmSipSysCall() failed, Status = (0x%x)\r\n", Status));
    goto ErrorExit;
  }
  if (SysCallRsp->common_rsp.status != 1)
  {
    Status = EFI_DEVICE_ERROR;
    DEBUG(( EFI_D_ERROR, "TZ_INFO_GET_FEATURE_VERSION_ID failed, Status = (0x%x)\r\n", SysCallRsp->common_rsp.status));
    goto ErrorExit;
  }

  TzDiagVersion = SysCallRsp->version;

ErrorExit:

  return Status;
}


EFI_STATUS QseeRegisterLogBuffer()
{
  EFI_STATUS                   Status;
  UINT32                       app_id = 0;
  VOID                        *log = NULL;
  QCOM_SCM_PROTOCOL           *QcomScmProtocol = NULL;
  qsee_register_log_buffer_t  *qsee_syscallp   = NULL;
  UINTN                        ShmBridgeSize   = QSEE_LOG_BUF_SIZE;

  Status = gBS->LocateProtocol (&gQcomScmProtocolGuid, NULL, (VOID**)&QcomScmProtocol);
  if (Status != EFI_SUCCESS)
    return Status;

  Status = gBS->LocateProtocol(&gEfiShmBridgeProtocolGuid, NULL, (VOID **)&ShmBridgeProtocol);
  if( Status != EFI_SUCCESS )
     return Status;

  Status = TzGetDiagVersion();
  if( Status != EFI_SUCCESS )
     return Status;

  DEBUG((EFI_D_ERROR, "TZ diag Version: 0x%x\n", TzDiagVersion));
  
  qsee_syscallp= (qsee_register_log_buffer_t*)AllocatePool(sizeof(qsee_register_log_buffer_t));
  if (NULL == qsee_syscallp)
  {
     DEBUG((EFI_D_WARN, "Failed to allocate memory:(size=%d)\n", sizeof(qsee_register_log_buffer_t)));
     return EFI_OUT_OF_RESOURCES;
  }

  log = ShmBridgeProtocol->ShmBridgeAllocate(ShmBridgeProtocol, &ShmBridgeSize, ShmBridgeBootSvcData);
  if (NULL == log)
  {
     Status =  EFI_OUT_OF_RESOURCES;
     DEBUG ((EFI_D_ERROR, "Failed to allocate memory:(size=%d) from SHMBridge\n", QSEE_LOG_BUF_SIZE));
     goto Exit;
  }

  SetMem(log, QSEE_LOG_BUF_SIZE, 0x0);

  SetMem(qsee_syscallp, sizeof(qsee_register_log_buffer_t), 0x0);
  qsee_syscallp->log_buffer_addr = (UINT64)(UINTN)log;
  qsee_syscallp->log_buffer_size = (UINT64)QSEE_LOG_BUF_SIZE;

  Status = QcomScmProtocol->ScmSendCommand(QcomScmProtocol,
                                           APP_REGISTER_LOG_BUF_COMMAND,
                                           &(app_id),
                                           qsee_syscallp,
                                           sizeof(qsee_register_log_buffer_t),
                                           NULL,
                                           0);

  if (Status != EFI_SUCCESS) 
  {
      DEBUG((EFI_D_ERROR, "Failed to send register log buffer commnd: %d\n", Status));
      goto Exit;
  }

  // Register event for exit BS
  Status = gBS->CreateEventEx( EVT_NOTIFY_SIGNAL,
                               TPL_CALLBACK,
                               ExitBootQseeLogHandler,
                               NULL,
                              &gEfiEventExitBootServicesGuid,
                              &ExitBootServicesQseeLogEvent );
  if (Status != EFI_SUCCESS) 
  {
     DEBUG(( EFI_D_ERROR, "CreateEventEx() failed for QseeLog ---, Status = (0x%p)\r\n", Status));
     goto Exit;
  }

  log_buffer = log;
  return Status;

Exit:

  if(qsee_syscallp != NULL)
  {
     qsee_syscallp->log_buffer_addr = 0;
     qsee_syscallp->log_buffer_size = 0;
     FreePool(qsee_syscallp);
     qsee_syscallp = NULL;
  }

  if( log != NULL )
  {
      ShmBridgeProtocol->ShmBridgeFree(ShmBridgeProtocol, log);
      log = NULL;
  }

  return Status;
}


/**
  This is called when notified that boot services has exited

  @param  IN     Event          The event to be signaled.
  @param  IN OUT *Context       A pointer to event context.

  @retval VOID   

**/
VOID EFIAPI ExitBootQseeLogHandler(
  IN EFI_EVENT  Event,
  IN VOID      *Context
)
{
  SetMem(log_buffer, QSEE_LOG_BUF_SIZE, 0x0);

  ShmBridgeProtocol->ShmBridgeFree(ShmBridgeProtocol, log_buffer);

  log_buffer = NULL;
  
  return;
}


EFI_STATUS DisplayQseeLog(UINT32 startOffset, UINT32 endOffset)
{
  EFI_STATUS    ret             = EFI_SUCCESS;
  UINT32        MaxBufSize      = 0;
  UINT32        LogBufSize      = 0;
  UINT32        LogBufFirstHalf = 0;
  void         *pLogBuf         = NULL;
  UINT8        *log             = NULL;

  if(log_buffer == NULL)
    return EFI_DEVICE_ERROR;
  
  if(TzDiagVersion < (UINT32)TZ_DIAG_LATEST_VERSION) // TZ Diag version less than 9.2.0
  {
    MaxBufSize = QSEE_LOG_BUF_SIZE - sizeof(struct tzdbg_log_pos_t);
    log = ((UINT8*)log_buffer+sizeof(struct tzdbg_log_pos_t));
  }
  else // TZ diag version 9.2.0 and above
  {
    MaxBufSize = QSEE_LOG_BUF_SIZE - sizeof(struct tzdbg_log_ver2_pos_t);
    log = ((UINT8*)log_buffer+sizeof(struct tzdbg_log_ver2_pos_t));
  }
  if (startOffset < endOffset)
  {
    LogBufSize = endOffset - startOffset;
    pLogBuf = AllocatePool(LogBufSize);
    if (NULL == pLogBuf)
    {
      ret = EFI_DEVICE_ERROR;
      DEBUG ((EFI_D_ERROR, "Failed to alloc buffer to print Qsee Log:%u\n", LogBufSize));
      goto Exit;
    }
    SetMem(pLogBuf, LogBufSize, 0);
    CopyMem(pLogBuf, (void *)(log + startOffset), LogBufSize);
  }
  else if ( endOffset < startOffset)
  {
    LogBufSize =  MaxBufSize - (startOffset - endOffset);
    LogBufFirstHalf = MaxBufSize - startOffset;
    pLogBuf = AllocatePool(LogBufSize);
    if (NULL == pLogBuf)
    {
      ret = EFI_DEVICE_ERROR;
      DEBUG ((EFI_D_ERROR, "Failed to alloc buffer to print TZ Log:%u\n", LogBufSize));
      goto Exit;
    }
    SetMem(pLogBuf, LogBufSize, 0);
    CopyMem(pLogBuf, (void *)(log + startOffset), LogBufFirstHalf);
    CopyMem((void *)(pLogBuf+ LogBufFirstHalf), log, endOffset);
  }
  else //endOffset == startOffset (no log is updated)
  {
    ret = EFI_SUCCESS;
    goto Exit;
  }

  SerialPortWrite((UINT8 *)pLogBuf, (UINTN)(LogBufSize));
  FreePool(pLogBuf);

Exit:
  return ret;
}

