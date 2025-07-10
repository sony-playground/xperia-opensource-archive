/** @file ScmArmV8.c

  ScmDxe provides secure channel messaging functions to communicate with Trust Zone.

  Copyright (c) 2014-2020, 2023 Qualcomm Technologies, Inc.
  All Rights Reserved.
  Confidential and Proprietary - Qualcomm Technologies, Inc.

**/
/*=============================================================================
                              EDIT HISTORY


 when       who     what, where, why
 --------   ---     --------------------------------------------------------------------------
 10/26/20   shl     Enabled ScmArmV8QseeSysCall API
 10/26/20   shl     Changed to 64 bit to align with TZ syscall structures
 10/05/20   shl     Supported ScmArmV8SysCall, which will handle the listener request from TZ.
 06/25/20   pr      Allocated uncached memory for Embedded app names and fixed tz diag version
 06/08/20   shl     Added support for 32 bit target for Qsee log buufer, and len check
 05/14/20   pr      Changes to adopt new Qsee diag version structure
 05/13/20   shl     Fixed the memory leak in case APP_START_EMBEDDED_APP_CMD:
                    added load tz test exec image support 
 04/12/20   shl     Added SMC invoke support 
 04/09/20   shl     Added event for calling exit boot sevice handler at last and reorg.
 11/13/19   shl     Reverted previous change
 10/02/19   shl     Removed QseecommDxe.h
 09/19/19   shl     Ported some changes and reorg the code
 07/22/19   shl     Expose listener callback to passthrough API ScmArmV8SipSysCall()
 07/02/19   yg      Lock to make sure buffer locked in TZ will not be touched
 09/27/18   pj      Updates to enable loading of TZ-embedded common libs and tpm TA
 09/15/18   pr      Raised TPL level at SMC disptach to TZ
 09/13/18   shl     Revert to previous version
 07/14/18   shl     Split TreeDxe, fromating
 06/14/18   pj      TPM app separation from winsecapp
 05/03/18   pj      Ported SHMBridge changes to Poipu
 10/24/17   pr      Copy SMC command failure return value to Rsp buffer
 06/18/16   rj      Added register log buffer command
 02/18/15   sm      Changed SMC to not truncate parameters to 32bit
 12/22/14   sm      Changed allocation to happen on initialization
 07/16/14   sm      Branched from ScmDxe

 ===========================================================================================*/
#include <Uefi.h>
#include <object.h>
#include <Guid/EventGroup.h>
#include <Library/DebugLib.h>
#include <Library/UefiLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UncachedMemoryAllocationLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/UefiCfgLib.h>
#include <Protocol/EFIScm.h>
#include <Protocol/EFIShmBridge.h>
#include "tz_interface_armv8.h"
#include "qsee_interface_armv8.h"
#include "tz_syscall.h"
#include "Listener.h"
#include "LogBuffer.h"

#ifdef SMC_INVOKE_SUPPORT
#include "SmcInvoke/SmcInvokeApi.h"
#endif //SMC_INVOKE_SUPPORT

#ifdef SMC_INVOKE_COMPAT_SUPPORT 
#include "SmcInvoke/SmcInvokeCompatApi.h"
#endif //SMC_INVOKE_COMPAT_SUPPORT


 // 64bit SMC call version
extern SmcErrnoType tz_armv8_smc_call( uint32 smc_id, 
                                       uint32 param_id, 
                                       uint64 parameters[4],
                                       uint64 *trusted_os_id );

extern VOID  *log_buffer;
extern UINT32 TzDiagVersion;

#define NUM_DIRECT_REQUEST_PARAMETERS     4
#define NUM_INDIRECT_REQUEST_PARAMETERS   7
#define INDIRECT_REQUEST_PARAMETER        3
#define INITIAL_REQ_SIZE                  (8 * 1024)

typedef struct _SMC_ARG_LIST_32 {
    UINT32 Args[NUM_INDIRECT_REQUEST_PARAMETERS];
} SMC_ARG_LIST_32;

typedef struct _SMC_ARG_LIST_64 {
    UINT64 Args[NUM_INDIRECT_REQUEST_PARAMETERS];
} SMC_ARG_LIST_64;

// GLOBALs
static SMC_ARG_LIST_64   *IndirectParameters = NULL;
static VOID              *ReqPtr = NULL;
static UINTN              CurrentReqSize = 0;

static EFI_SHMBRIDGE_PROTOCOL *ShmBridgeProtocol;

#define PAGE_SIZE       4096
#define ALIGN_UP(size, alignment)  (((size) + ((alignment)-1)) & ~((alignment)-1))
#define PAGE_ALIGN(x)   ALIGN_UP(x, PAGE_SIZE)  

EFI_EVENT  ExitBootServicesScmDxeV8Event;

EFI_STATUS ScmArmV8ExitBootServicesHandler( IN QCOM_SCM_PROTOCOL  *This );


VOID EFIAPI ExitBootServicesScmDxeV8EventHandler
(
  IN EFI_EVENT Event,
  IN VOID *Context
)
{
   EFI_STATUS  Status = ScmArmV8ExitBootServicesHandler( NULL );
   if ( EFI_ERROR(Status))
      DEBUG(( EFI_D_INFO, "ScmArmV8ExitBootServicesHandler failed  0x%x \r\n", Status));

   return;
}


EFI_STATUS
ScmArmV8Initialize(VOID)
{
   EFI_STATUS Status = EFI_SUCCESS;
   UINTN Size = sizeof(SMC_ARG_LIST_64);

   Status = gBS->LocateProtocol(&gEfiShmBridgeProtocolGuid, NULL, (VOID **)&ShmBridgeProtocol);
   ASSERT_EFI_ERROR(Status);

   // ShmBridgeFree won't be called for this allocation. Allocation will be freed 
   // when the Shmbridge is being deleted upon ExitBootServices callback. 
   IndirectParameters = (SMC_ARG_LIST_64*)ShmBridgeProtocol->ShmBridgeAllocate( ShmBridgeProtocol, 
                                                                               &Size, 
                                                                                ShmBridgeBootSvcData );
   if (IndirectParameters == NULL)
   {
      Status = EFI_OUT_OF_RESOURCES;
      goto ErrorExit;
   }

   Size = INITIAL_REQ_SIZE;
   // ShmBridgeFree won't be called for this allocation. Allocation will be freed 
   // when the Shmbridge is being deleted upon ExitBootServices callback. 
   ReqPtr = ShmBridgeProtocol->ShmBridgeAllocate( ShmBridgeProtocol, 
                                                 &Size,
                                                  ShmBridgeBootSvcData);
   if (ReqPtr == NULL)
   {
      // Free allocation for IndirectParameters
      ShmBridgeProtocol->ShmBridgeFree(ShmBridgeProtocol, IndirectParameters);
      Status = EFI_OUT_OF_RESOURCES;
      goto ErrorExit;
   }

   CurrentReqSize = INITIAL_REQ_SIZE;

#ifdef SMC_INVOKE_SUPPORT
    Status = SmcInvokeInit();
    if( Status != EFI_SUCCESS )
       goto ErrorExit;
#endif //SMC_INVOKE_SUPPORT 

#ifdef SMC_INVOKE_COMPAT_SUPPORT
    Status = SmcInvokeCompatInit();
    if( Status != EFI_SUCCESS )
       goto ErrorExit;
#endif //SMC_INVOKE_COMPAT_SUPPORT 

   Status = gBS->CreateEventEx ( EVT_NOTIFY_SIGNAL,
                                 TPL_CALLBACK,
                                 ExitBootServicesScmDxeV8EventHandler,
                                 NULL,
                                &gEfiEventExitBootServicesSuccessGuid,
                                &ExitBootServicesScmDxeV8Event);
ErrorExit:
    
    return Status;
}


EFI_STATUS
SmcInvokeCompatCall(
    IN  UINT32            SmcId,
    IN  UINT32            ParamId,
    IN  UINT64            Parameters[SCM_MAX_NUM_PARAMETERS],
    OUT UINT64            Results[SCM_MAX_NUM_RESULTS],
    IN  BOOLEAN          *Processed
    )
{
   EFI_STATUS  Status    = EFI_SUCCESS;

   *Processed = TRUE;

   switch( SmcId )
   { 

#ifdef SMC_INVOKE_COMPAT_SUPPORT

      case TZ_OS_APP_START_ID:
         Status = SmcInvokeCompatStartApp((void *)(UINTN)Parameters[2], 
                                                         Parameters[1],
                                              (UINT32 *)&Results[3]);
         Results[0] = Status;
         Results[1] = Status;
         Results[2] = QSEE_APP_ID;
         break;

      case TZ_OS_APP_SHUTDOWN_ID:
         Status = SmcInvokeCompatShutdownApp( (UINT32 )Parameters[0] );
         Results[0] = Status;
         Results[1] = Status;
         Results[2] = QSEE_APP_ID;
         Results[3] = Parameters[0];
         break;

      case TZ_OS_APP_LOOKUP_ID:
         Status = SmcInvokeCompatLookupAppId((void *)(UINTN)Parameters[0],
                                                            Parameters[1],
                                                 (UINT32 *)&Results[3] );
         Results[0] = Status;
         Results[1] = Status;
         Results[2] = QSEE_APP_ID;
         break;

      case TZ_APP_QSAPP_SEND_DATA_ID:
         Status = SmcInvokeCompatSendCmd( Parameters[0], 
                           (void *)(UINTN)Parameters[1],
                                          Parameters[2],
                           (void *)(UINTN)Parameters[3], 
                                          Parameters[4]);
         Results[0] = Status;
         Results[1] = Status;
         Results[2] = QSEE_APP_ID;
         break;

#endif //SMC_INVOKE_COMPAT_SUPPORT

       default:
         *Processed = FALSE;
         break;
   }

   return Status;

}


EFI_STATUS
SysCallInternal(
    IN  UINT32               SmcId,
    IN  UINT32               ParamId,
    IN  UINT64               Parameters[SCM_MAX_NUM_PARAMETERS],
    OUT UINT64               Results[SCM_MAX_NUM_RESULTS],
    OUT UINT64              *TrustedOsId
    )
{
    EFI_STATUS            Status = EFI_SUCCESS;
    SmcErrnoType          TzStatus;
    UINT64                DirectParameters[NUM_DIRECT_REQUEST_PARAMETERS] = { 0 };
    UINT64                InternalTrustedOsId;
    UINTN                 i, NumArguments;

    if (Parameters == NULL || Results == NULL)
    {
        return EFI_INVALID_PARAMETER;
    }

    NumArguments = ParamId & TZ_SYSCALL_PARAM_NARGS_MASK;

    if (NumArguments > SCM_MAX_NUM_PARAMETERS)
    {
        Status = EFI_INVALID_PARAMETER;
        goto ErrorExit;
    }
    else if (NumArguments > NUM_DIRECT_REQUEST_PARAMETERS)
    {
        for (i = 0; i < INDIRECT_REQUEST_PARAMETER; i++)
        {
            DirectParameters[i] = Parameters[i];
        }

        DirectParameters[INDIRECT_REQUEST_PARAMETER] = (UINTN)IndirectParameters;

        for (i = INDIRECT_REQUEST_PARAMETER; i < NumArguments; i++)
        {
            IndirectParameters->Args[i - INDIRECT_REQUEST_PARAMETER] = Parameters[i];
        }
    }
    else
    {
        for (i = 0; i < NumArguments; i++)
        {
            DirectParameters[i] = Parameters[i];
        }
    }

    TzStatus = tz_armv8_smc_call( SET_BIT(SmcId, AARCH_BIT),
                                  ParamId,
                                  DirectParameters,
                                 &InternalTrustedOsId );
    if (TzStatus != SMC_SUCCESS)
    {
        DEBUG((EFI_D_ERROR, "tz_armv8_smc_call failed, TzStatus = 0x%x,  SmcId = 0x%x  \r\n", TzStatus, SmcId ));

        Results[0] = DirectParameters[0];

        if (TzStatus == SMC_ERR_UNKNOWN_SMC_ID)
        {
            Status = EFI_UNSUPPORTED;
        }
        else if (TzStatus == SMC_ERR_SYSCALL_FAILED && (INT32)Results[0] == TZ_RETURN_ALREADY_DONE)
        {
            Status = EFI_ALREADY_STARTED;
        }
        else
        {
            Status = EFI_DEVICE_ERROR;
        }
    }
    else
    {
        Results[0] = TZ_RETURN_SUCCESS;

        for (i = 0; i < SCM_MAX_NUM_RESULTS - 1; i++)
        {
            Results[i + 1] = DirectParameters[i];
        }
    }

    if (TrustedOsId != NULL)
    {
        *TrustedOsId = InternalTrustedOsId;
    }

ErrorExit:

    return Status;
}


EFI_STATUS
QseeSysCallInternal(
    IN  UINT32               SmcId,
    IN  UINT32               ParamId,
    IN  UINT64               Parameters[SCM_MAX_NUM_PARAMETERS],
    OUT UINT64               Results[SCM_MAX_NUM_RESULTS]
    )
{
    EFI_STATUS                  Status;
    UINT32                      QseeSmcId;
    UINT32                      QseeParamId;
    UINT64                      QseeParameters[SCM_MAX_NUM_PARAMETERS] = { 0 };
    UINT64                      QseeResults[SCM_MAX_NUM_RESULTS] = { 0 };
    UINT64                      QseeTrustedOsId;
    qsee_command_resp_info_t   *QseeRsp;
    UINT32                      ListenerId;
    BOOLEAN                     Processed = FALSE;
    tzdbg_log_t                 *log = NULL;
    UINT32                      QseeLogStart = 0;
    UINT32                      QseeLogNewStart = 0;
    tzos_listener_response_handler_t *ListenerCmdPtr = (tzos_listener_response_handler_t*)QseeParameters;

   // smc invoke compat call first
   Status = SmcInvokeCompatCall(  SmcId,
                                  ParamId,
                                  Parameters,
                                  Results,
                                 &Processed);
   if( Processed )
      return Status;

    QseeSmcId = SmcId;
    QseeParamId = ParamId;
    QseeTrustedOsId = 0;
    CopyMem(QseeParameters, Parameters, SCM_MAX_NUM_PARAMETERS * sizeof(UINT64));

    if (log_buffer && (SmcId == TZ_OS_APP_START_ID || SmcId == TZ_OS_APP_SHUTDOWN_ID ||
        SmcId == TZ_APP_QSAPP_SEND_DATA_ID || SmcId == TZ_OS_APP_START_EMBEDDED_ID))
    {
        if(TzDiagVersion < (UINT32)TZ_DIAG_LATEST_VERSION) // TZ diag version less than 9.1.0
        {
            log = (tzdbg_log_t*)log_buffer;
            QseeLogStart = (UINT32)(log->log_pos.log_Legacyheader.offset);
        }
        else // TZ diag version 9.1.0 and above
        {
            log = (tzdbg_log_t*)log_buffer;
            QseeLogStart = (UINT32)(log->log_pos.log_Latestheader.offset);
        }
    }

    do
    {
        Status = SysCallInternal( QseeSmcId,
                                  QseeParamId,
                                  QseeParameters,
                                  QseeResults,
                                 &QseeTrustedOsId );
        if (Status != EFI_SUCCESS)
        {
            QseeRsp = (qsee_command_resp_info_t*)Results;
            QseeRsp->result = QseeResults[0];
            break;
        }

        QseeRsp = (qsee_command_resp_info_t*)QseeResults;

        if ( QseeRsp->result == TZOS_RESULT_INCOMPLETE )
        {
            ListenerId = QseeRsp->data;

            Status = ListenerExec( ListenerId );
            if (Status != EFI_SUCCESS)
            {
                DEBUG((EFI_D_ERROR, "Listener Callback function failed. id 0x%x\r\n", ListenerId));
                DEBUG((EFI_D_ERROR, "QseeSmcId  0x%x   QseeParamId  0x%x  \r\n", QseeSmcId, QseeParamId));
                ListenerCmdPtr->status = TZOS_RESULT_FAILURE;
            }
            else
            {
                ListenerCmdPtr->status = TZOS_RESULT_SUCCESS;
            }

            ListenerCmdPtr->listener_id = ListenerId;

            QseeSmcId = TZ_OS_LISTENER_RESPONSE_HANDLER_ID;
            QseeParamId = TZ_OS_LISTENER_RESPONSE_HANDLER_ID_PARAM_ID;
        }
        else
        {
            // No listener request. Save results.
            CopyMem(Results, QseeResults, SCM_MAX_NUM_RESULTS * sizeof(UINT64));
            break;
        }

    } while (TRUE);

    if (log_buffer && (SmcId == TZ_OS_APP_START_ID || SmcId == TZ_OS_APP_SHUTDOWN_ID ||
        SmcId == TZ_APP_QSAPP_SEND_DATA_ID || SmcId == TZ_OS_APP_START_EMBEDDED_ID))
    {
        if(TzDiagVersion < (UINT32)TZ_DIAG_LATEST_VERSION) // TZ diag version less than 9.2.0
        {
            QseeLogNewStart = (UINT32)(log->log_pos.log_Legacyheader.offset);
        }
        else // TZ diag version 9.2.0 and above
        {
            QseeLogNewStart = (UINT32)(log->log_pos.log_Latestheader.offset);
        }
        DisplayQseeLog(QseeLogStart, QseeLogNewStart);
    }

    return Status;
}


/**
   This API will NOT handle listener request from TZ.
*/
EFI_STATUS
ScmArmV8SipSysCall(
    IN  QCOM_SCM_PROTOCOL   *This,
    IN  UINT32               SmcId,
    IN  UINT32               ParamId,
    IN  UINT64               Parameters[SCM_MAX_NUM_PARAMETERS],
    OUT UINT64               Results[SCM_MAX_NUM_RESULTS]
    )
{ 
   EFI_STATUS  Status = EFI_SUCCESS;
   EFI_TPL     PrevTPL = 0;

   PrevTPL = gBS->RaiseTPL(TPL_CALLBACK);

   Status = SysCallInternal( SmcId,
                             ParamId,
                             Parameters,
                             Results,
                             NULL );

   gBS->RestoreTPL(PrevTPL);

   return Status;

}


/**
   This API will handle listener request from TZ.
*/
EFI_STATUS
ScmArmV8QseeSysCall(
    IN  QCOM_SCM_PROTOCOL   *This,
    IN  UINT32               SmcId,
    IN  UINT32               ParamId,
    IN  UINT64               Parameters[SCM_MAX_NUM_PARAMETERS],
    OUT UINT64               Results[SCM_MAX_NUM_RESULTS]
    )
{
   EFI_STATUS  Status;
   EFI_TPL     PrevTPL = 0;

   PrevTPL = gBS->RaiseTPL(TPL_CALLBACK);

   Status = QseeSysCallInternal( SmcId,
                                 ParamId,
                                 Parameters,
                                 Results );

   gBS->RestoreTPL(PrevTPL);

   return Status;
}


/**
  This function calls into trust zone; any non-qsee command should use this interface.
  Does tranlation from old interface into new interface.

  @param[in/out]        Cmd    Command data passed into trust zone.

  @return       EFI_SUCCESS:   Function completed successfully.
           EFI_DEVICE_ERROR:   Failed
*/
EFI_STATUS
ScmArmV8SysCall(
    IN     QCOM_SCM_PROTOCOL      *This,
    IN OUT const VOID             *Cmd
    )
{
    return EFI_UNSUPPORTED;
}


/**
  This function is unsupported

  @param[in/out]          Id    Token Id
  @param[in]          Param0    parameter 0
  @param[in]          Param1    parameter 1

  @return  EFI_DEVICE_UNSUPPORTED:  This function is unsupported
*/
EFI_STATUS
ScmArmV8FastCall(
    IN QCOM_SCM_PROTOCOL     *This,
    IN UINT32                 Id,
    IN UINT32                 Param0,
    IN UINT32                 Param1
    )
{
    return EFI_UNSUPPORTED;
}


/**
  This function calls into trust zone to get TZ version

  @param[in/out]    Version    Pointer to TZ version address.

  @return       EFI_SUCCESS:   Function completed successfully.
           EFI_DEVICE_ERROR:   Failed
*/
EFI_STATUS
ScmArmV8GetVersion(
    IN     QCOM_SCM_PROTOCOL      *This,
    IN OUT UINT32                 *Version
    )
{
    return EFI_UNSUPPORTED;
}


EFI_STATUS
ScmArmV8SendCommand(
    IN     QCOM_SCM_PROTOCOL      *This,
    IN     AppCmdType              CmdId,
    IN     UINT32                 *AppId,
    IN OUT VOID                   *Req,
    IN     UINTN                   ReqLen,
    IN OUT VOID                   *Rsp,
    IN     UINTN                   RspLen
    )
{
    EFI_STATUS                      Status = EFI_INVALID_PARAMETER;
    UINT32                          SmcId;
    UINT32                          ParamId;
    UINT64                          Parameters[SCM_MAX_NUM_PARAMETERS] = { 0 };
    UINT64                          Results[SCM_MAX_NUM_RESULTS] = { 0 };
    UINTN                           ReqSize;
    UINT64                         *Request = Req;
    UINT8                          *AppNameString = NULL;
    // The following are used for typecasting Paremeters to specific type of SysCall
    tzos_app_start_t               *AppStartSysCall;
    tzos_app_shutdown_t            *AppShutdownSysCall;
    tzos_app_lookup_t              *AppLookupSysCall;
    tzapp_qsapp_send_data_t        *AppSendDataSyCall;
    tzos_load_services_image_t     *ServImageSysCall;
    tzos_app_region_type_t         *AppsRegionSyscall;
    tzos_rpmb_provision_key_t      *ProvisionRpmbKey;
    qsee_command_resp_info_t       *QseeResponse;
    tzos_log_buffer_type_t         *LogBufferSyscall;
    tzos_app_start_embedded_t      *StartEmbeddedAppSyscall;
    tzos_load_external_image_t     *LoadExternalImageCall; 
    EFI_TPL                         PrevTPL = 0;

    // Coming from external of ScmDxe, check the pointer, other pointers are checked case by case.
    if (This == NULL)
    {
        return EFI_INVALID_PARAMETER;
    }

    /* Make sure to grab the Lock (this will acquire DxeLock) to make sure the buffer
     * locked by TZ for the service in progress is not touched by another request
     * originated before the first one completes. This scenario is possible in multi
     * threaded environment and touching the buffer will cause XPU violation */
    PrevTPL = gBS->RaiseTPL(TPL_CALLBACK);

    //Create the QSEE commands here, need to consult with owner what is memory requirement here.
    switch (CmdId)
    {
    case  APP_START_APP_CMD:
        if (Req == NULL)
        {
            goto ErrorExit;
        }

        AppStartSysCall = (tzos_app_start_t*)Parameters;
        AppStartSysCall->mdt_len = Request[0];
        AppStartSysCall->img_len = Request[1];
        AppStartSysCall->pa = Request[2];
        SmcId = TZ_OS_APP_START_ID;
        ParamId = TZ_OS_APP_START_ID_PARAM_ID;

        break;

    case  APP_SHUTDOWN_CMD:
        if (AppId == NULL)
        {
            goto ErrorExit;
        }

        AppShutdownSysCall = (tzos_app_shutdown_t*)Parameters;
        AppShutdownSysCall->app_id = *AppId;
        SmcId = TZ_OS_APP_SHUTDOWN_ID;
        ParamId = TZ_OS_APP_SHUTDOWN_ID_PARAM_ID;

        break;

    case  APP_QUERY_APPID_CMD:
        if (AppId == NULL || Req == NULL || ReqLen == 0 || ReqLen > QSEE_MAX_NAME_SIZE)
        {
            goto ErrorExit;
        }

        AppLookupSysCall = (tzos_app_lookup_t*)Parameters;
        AppLookupSysCall->app_name = (UINTN)ReqPtr;
        CopyMem((VOID*)(UINTN)AppLookupSysCall->app_name, Req, ReqLen);
        AppLookupSysCall->name_len = ReqLen;
        SmcId = TZ_OS_APP_LOOKUP_ID;
        ParamId = TZ_OS_APP_LOOKUP_ID_PARAM_ID;

        break;

    case  APP_SEND_DATA_CMD:
        if (AppId == NULL || Req == NULL || Rsp == NULL || (ReqLen + RspLen) == 0)
        {
            goto ErrorExit;
        }

        // special memory requirement here, 4K multiple aligned at 4K for both req+rsp
        if (PAGE_ALIGN( ReqLen ) > SIZE_MAX - PAGE_ALIGN( RspLen ))
        {
            Status = EFI_BAD_BUFFER_SIZE;
            goto ErrorExit;
        }
        ReqSize = PAGE_ALIGN( ReqLen ) + PAGE_ALIGN( RspLen );

    ReallocateReq:
        if (ReqPtr == NULL)
        {
            // ShmBridgeFree won't be called for this allocation. Allocation will be freed 
            // when the Shmbridge is being deleted upon ExitBootServices callback. 
            ReqPtr = ShmBridgeProtocol->ShmBridgeAllocate(ShmBridgeProtocol, &ReqSize, ShmBridgeBootSvcData);
            if (ReqPtr == NULL)
            {
                Status = EFI_OUT_OF_RESOURCES;
                goto ErrorExit;
            }
            CurrentReqSize = ReqSize;
            DEBUG((EFI_D_INFO, "UncachedAllocateAlignedPool  ---, ReqSize = %d\r\n", ReqSize));
        }
        else
        {
            if (ReqSize > CurrentReqSize)
            {
                // In general, allocation will be freed when the Shmbridge is being deleted upon 
                // ExitBootServices callback. Allocation being freeed happens only resize is required.
                ShmBridgeProtocol->ShmBridgeFree(ShmBridgeProtocol, ReqPtr);
                ReqPtr = NULL;
                CurrentReqSize = 0;
                goto ReallocateReq;
            }
        }

        // assign allocated memory
        AppSendDataSyCall = (tzapp_qsapp_send_data_t*)Parameters;
        AppSendDataSyCall->req_ptr = (UINTN)ReqPtr;
        AppSendDataSyCall->rsp_ptr = (UINTN)((UINT8*)ReqPtr + PAGE_ALIGN(ReqLen));
        AppSendDataSyCall->app_id = *AppId;
        CopyMem((VOID*)(UINTN)AppSendDataSyCall->req_ptr, Req, ReqLen);
        AppSendDataSyCall->req_len = ReqLen;
        CopyMem((VOID*)(UINTN)AppSendDataSyCall->rsp_ptr, Rsp, RspLen);
        AppSendDataSyCall->rsp_len = RspLen;
        SmcId = TZ_APP_QSAPP_SEND_DATA_ID;
        ParamId = TZ_APP_QSAPP_SEND_DATA_ID_PARAM_ID;

        break;

    case  APP_LOAD_SERV_IMAGE_CMD:
        if (Req == NULL)
        {
            goto ErrorExit;
        }

        ServImageSysCall = (tzos_load_services_image_t*)Parameters;
        ServImageSysCall->mdt_len = Request[0];
        ServImageSysCall->img_len = Request[1];
        ServImageSysCall->pa = Request[2];
        SmcId = TZ_OS_LOAD_SERVICES_IMAGE_ID;
        ParamId = TZ_OS_LOAD_SERVICES_IMAGE_ID_PARAM_ID;

        break;

    case  APP_REGION_NOTIFICATION_CMD:
        if (Req == NULL)
        {
            goto ErrorExit;
        }

        AppsRegionSyscall = (tzos_app_region_type_t*)Parameters;
        AppsRegionSyscall->app_rgn_addr = Request[0];
        AppsRegionSyscall->app_rgn_size = Request[1];
        SmcId = TZ_OS_APP_REGION_NOTIFICATION_ID;
        ParamId = TZ_OS_APP_REGION_NOTIFICATION_ID_PARAM_ID;

        break;

    case APP_REGISTER_LOG_BUF_COMMAND:
        if (Req == NULL)
        {
            goto ErrorExit;
        }
        LogBufferSyscall = (tzos_log_buffer_type_t*)Parameters;
        LogBufferSyscall->log_addr = Request[0];
        LogBufferSyscall->log_size = Request[1];
        SmcId = TZ_OS_REGISTER_LOG_BUFFER_ID;
        ParamId = TZ_OS_REGISTER_LOG_BUFFER_ID_PARAM_ID;

        break;

    case APP_PROVISION_RPMB_KEY_COMMAND:
        if (Req == NULL || ReqLen == 0 || Rsp == NULL || RspLen == 0)
        {
            goto ErrorExit;
        }

        ProvisionRpmbKey = (tzos_rpmb_provision_key_t*)Parameters;
        ProvisionRpmbKey->key_type = Request[0];
        SmcId = TZ_OS_RPMB_PROVISION_KEY_ID;
        ParamId = TZ_OS_RPMB_PROVISION_KEY_ID_PARAM_ID;

        break;

    case APP_RPMB_ERASE_COMMAND:
        if (Rsp == NULL || RspLen == 0)
        {
            goto ErrorExit;
        }

        SmcId = TZ_OS_RPMB_ERASE_ID;
        ParamId = TZ_OS_RPMB_ERASE_ID_PARAM_ID;

        break;

    case APP_RPMB_CHECK_PROV_STATUS_COMMAND:
        if (Rsp == NULL || RspLen == 0)
        {
            goto ErrorExit;
        }

        SmcId = TZ_OS_RPMB_CHECK_PROV_STATUS_ID;
        ParamId = TZ_OS_RPMB_CHECK_PROV_STATUS_ID_PARAM_ID;

        break;

    case  APP_QUERY_EMBEDDED_IMAGES_SUPPORT_CMD:

        SmcId = TZ_OS_QUERY_EMBEDDED_IMAGES_SUPPORT_ID;
        ParamId = TZ_OS_QUERY_EMBEDDED_IMAGES_SUPPORT_PARAM_ID;

        break;

    case APP_START_EMBEDDED_APP_CMD:
        if (AppId == NULL || Req == NULL || ReqLen == 0 || ReqLen > 64 )
        {
            goto ErrorExit;
        }

        AppNameString = ShmBridgeProtocol->ShmBridgeAllocate(ShmBridgeProtocol, &ReqLen, ShmBridgeBootSvcData);
        if (AppNameString == NULL)
        {
            Status = EFI_OUT_OF_RESOURCES;
            goto ErrorExit;
        }

        StartEmbeddedAppSyscall = (tzos_app_start_embedded_t*)Parameters;
        StartEmbeddedAppSyscall->app_name = (UINTN)AppNameString;
        CopyMem((VOID*)(UINTN)StartEmbeddedAppSyscall->app_name, Req, ReqLen);
        StartEmbeddedAppSyscall->app_name_len = ReqLen;

        SmcId = TZ_OS_APP_START_EMBEDDED_ID;
        ParamId = TZ_OS_APP_START_EMBEDDED_ID_PARAM_ID;

        break;

    case APP_START_TZTESTEXEC_APP_CMD:
        if (Req == NULL)
        {
            goto ErrorExit;
        }

        LoadExternalImageCall = (tzos_load_external_image_t *)Parameters;
        LoadExternalImageCall->mdt_len = Request[0];
        LoadExternalImageCall->img_len = Request[1];
        LoadExternalImageCall->pa = Request[2];
        SmcId = TZ_OS_LOAD_TZTESTEXEC_IMAGE_ID;
        ParamId = TZ_OS_LOAD_TZTESTEXEC_IMAGE_ID_PARAM_ID;

        break;

    default:
        Status = EFI_UNSUPPORTED;
        goto ErrorExit;
    }

    Status = QseeSysCallInternal( SmcId,
                                  ParamId,
                                  Parameters,
                                  Results );

    QseeResponse = (qsee_command_resp_info_t*)Results;

    // Check QSEE result.
    if (QseeResponse->result != TZOS_RESULT_SUCCESS)
    {
        // pass the result to caller through Rsp
        // for RPMB provision and erase specially return Status is bad in this case., Rsp can't be trusted.
        // only RPMB provision and erase cases care this value so far.
        if ((CmdId == APP_PROVISION_RPMB_KEY_COMMAND || CmdId == APP_RPMB_ERASE_COMMAND || CmdId == APP_RPMB_CHECK_PROV_STATUS_COMMAND) &&
             RspLen > 3 )
        {
            *((UINT32 *)Rsp) = QseeResponse->result;
        }

        DEBUG((EFI_D_ERROR, "QseeResponse->result = 0x%x\r\n", QseeResponse->result));

        Status = EFI_DEVICE_ERROR;
    }

    if (Status != EFI_SUCCESS)
    {
        DEBUG((EFI_D_ERROR, "Status = 0x%x\r\n", Status));
        goto ErrorExit;
    }

    if (QseeResponse->resp_type == QSEE_APP_ID)
    {
        switch (CmdId)
        {
           case  APP_START_APP_CMD:
           case  APP_QUERY_APPID_CMD:
           case  APP_SHUTDOWN_CMD:
           case  APP_START_EMBEDDED_APP_CMD:

              *AppId = QseeResponse->data;
              break;

          case  APP_SEND_DATA_CMD:
            /*
            * Copying request data back to request buffer added to address CR 2104354.
            * It was observed that couple of SMC commands process request buffer data directly
            * or copy processed data back to request buffer only. In these cases to give processed
            * request data back to clients, below statement to copy request buffer added.
            */
              CopyMem(Req, (UINT8*)ReqPtr, ReqLen);
              CopyMem(Rsp, (UINT8*)ReqPtr + PAGE_ALIGN(ReqLen), RspLen);
              break;
 
          default:
              Status = EFI_UNSUPPORTED;
              goto ErrorExit;
        }
    }

ErrorExit:

    if(AppNameString != NULL)
        ShmBridgeProtocol->ShmBridgeFree(ShmBridgeProtocol, AppNameString);

    gBS->RestoreTPL(PrevTPL);

    return Status;

}


/**
  This function calls trust zone to register a callback function
  ScmDxe also keep a record of this registration.

  @param[in]   ListenerId         Listener ID.
  @param[in]   CallbackPtr        Pointer to callback fucntion.
  @param[in]   CallbackHandle     handle pointer from caller
  @param[in]   SharedBufferPtr
  @param[in]   SharedBufferLen

  @return            0:   Function completed successfully.
          Other values:   Failed
*/
EFI_STATUS
ScmArmV8RegisterCallback(
    IN QCOM_SCM_PROTOCOL             *This,
    IN UINT32                         ListenerId,
    IN QcomScmListenerCallbackPtr     CallbackPtr,
    IN VOID                          *CallbackHandle,
    IN UINT8                         *SharedBufferPtr,
    IN UINTN                          SharedBufferLen
    )
{
    EFI_STATUS                  Status = EFI_INVALID_PARAMETER;
    UINT64                      Parameters[SCM_MAX_NUM_PARAMETERS] = { 0 };
    UINT64                      Results[SCM_MAX_NUM_RESULTS] = { 0 };
    tzos_register_listener_t   *AppRegisterListenerSyscall;
    qsee_command_resp_info_t   *QseeResponse;
    EFI_TPL                     PrevTPL = 0;

    PrevTPL = gBS->RaiseTPL(TPL_CALLBACK);

    if( ListenerId == 0 && CallbackPtr == NULL && CallbackHandle == NULL &&
        SharedBufferPtr == NULL  && SharedBufferLen != 0  )
    {
       /* This is smc invoke support case, caller informs callback message length
          only maximum 500K is allowed */
       if( SharedBufferLen <= 0x80000 )
       { 
          SmcInvokeSetCbMsgBufLen( SharedBufferLen );
          Status = EFI_SUCCESS;
       }
       else
          DEBUG((EFI_D_ERROR, "smc invoke callback message length too large \r\n" ));

       goto ErrorExit;
    } 

    if( ListenerId == 0 || CallbackPtr == NULL )  
       goto ErrorExit;

    // register to local first  
    Status = ListenerRegister( ListenerId,
                               CallbackPtr,
                               CallbackHandle,
                               SharedBufferPtr,
                               SharedBufferLen );
    if( Status != EFI_SUCCESS )
    {
        DEBUG((EFI_D_ERROR, "Register ListenerId locally failed. id 0x%x\r\n", ListenerId ));
        goto ErrorExit;
    }

    // register to remote
    AppRegisterListenerSyscall = (tzos_register_listener_t*)Parameters;
    AppRegisterListenerSyscall->listener_id = ListenerId;
    AppRegisterListenerSyscall->req_ptr = (UINTN)SharedBufferPtr;
    AppRegisterListenerSyscall->req_len = SharedBufferLen;

    Status = QseeSysCallInternal( TZ_OS_REGISTER_LISTENER_SMCINVOKE_ID,
                                  TZ_OS_REGISTER_LISTENER_SMCINVOKE_ID_PARAM_ID,
                                  Parameters,
                                  Results );

    QseeResponse = (qsee_command_resp_info_t *)Results;

    if (Status != EFI_SUCCESS || QseeResponse->result != TZOS_RESULT_SUCCESS)
    {
       DEBUG((EFI_D_ERROR, "Register ListenerId remotely failed. id 0x%x\r\n", ListenerId ));
       ListenerDeregisterById( ListenerId );
    }

ErrorExit:

    gBS->RestoreTPL(PrevTPL);

    return Status;
}


/**
  Deregister listener service and delete entry from listener table

  @param  IN      This           Protocol pointer.
  @param  IN      ListenerId     Listener Id to be removed
  @retval EFI_STATUS Status

**/
EFI_STATUS
ScmArmV8DeRegisterCallback(
    IN QCOM_SCM_PROTOCOL  *This,
    IN UINT32             ListenerId
    )
{
    EFI_STATUS                   Status;
    UINT64                       Parameters[SCM_MAX_NUM_PARAMETERS] = { 0 };
    UINT64                       Results[SCM_MAX_NUM_RESULTS] = { 0 };
    tzos_deregister_listener_t  *AppDeregisterListenerSyscall;
    qsee_command_resp_info_t    *QseeResponse;
    EFI_TPL                      PrevTPL = 0;

    PrevTPL = gBS->RaiseTPL(TPL_CALLBACK);

    if( !IsListenerIdValid( ListenerId ))
    {
        Status = EFI_INVALID_PARAMETER;
        goto ErrorExit;
    }

    AppDeregisterListenerSyscall = (tzos_deregister_listener_t*)Parameters;
    AppDeregisterListenerSyscall->listener_id = ListenerId;

    Status = QseeSysCallInternal( TZ_OS_DEREGISTER_LISTENER_ID,
                                  TZ_OS_DEREGISTER_LISTENER_ID_PARAM_ID,
                                  Parameters,
                                  Results );

    QseeResponse = (qsee_command_resp_info_t*)Results;

    if( Status == EFI_SUCCESS && QseeResponse->result == TZOS_RESULT_SUCCESS )
       ListenerDeregisterById( ListenerId );
    else     
       DEBUG((EFI_D_ERROR, "Deregister ListenerId failed. \r\n"));

ErrorExit:

    gBS->RestoreTPL(PrevTPL);

    return Status;
}


/**
  This is called when notified that boot services has exited

  @param  IN      This         Protocol pointer.
  @retval EFI_STATUS Status

**/
EFI_STATUS
ScmArmV8ExitBootServicesHandler(
    IN QCOM_SCM_PROTOCOL  *This
    )
{
    EFI_STATUS                    Status = EFI_SUCCESS;
    UINT32                        Index;
    UINT64                        Parameters[SCM_MAX_NUM_PARAMETERS] = { 0 };
    UINT64                        Results[SCM_MAX_NUM_RESULTS] = { 0 };
    tzos_deregister_listener_t   *AppDeregisterListenerSyscall;
    qsee_command_resp_info_t     *QseeResponse;
    UINT32                        MaxTableSize;
    EFI_TPL                       PrevTPL = 0;

    PrevTPL = gBS->RaiseTPL(TPL_CALLBACK);

    AppDeregisterListenerSyscall = (tzos_deregister_listener_t*)Parameters;

    MaxTableSize = ListenerGetTableSize();
    for( Index = 0; Index < MaxTableSize; Index++ )
    {
        AppDeregisterListenerSyscall->listener_id = ListenerGetId( Index );

        if( AppDeregisterListenerSyscall->listener_id == 0 )
           continue;

        // deregister from remote first
        Status = QseeSysCallInternal(TZ_OS_DEREGISTER_LISTENER_ID,
                                     TZ_OS_DEREGISTER_LISTENER_ID_PARAM_ID,
                                     Parameters,
                                     Results);

        QseeResponse = (qsee_command_resp_info_t*)Results;

        if( Status != EFI_SUCCESS || QseeResponse->result != TZOS_RESULT_SUCCESS )
            DEBUG((EFI_D_ERROR, "Deregister ListenerId failed. \r\n"));

        // deregister from local no matter what
        ListenerDeregisterByIndex( Index );
    }

#ifdef SMC_INVOKE_COMPAT_SUPPORT
    SmcInvokeCompatDeinit();
#endif //SMC_INVOKE_COMPAT_SUPPORT

#ifdef SMC_INVOKE_SUPPORT
    SmcInvokeDeinit();
#endif //SMC_INVOKE_SUPPORT

    if( IndirectParameters )
       ShmBridgeProtocol->ShmBridgeFree(ShmBridgeProtocol, IndirectParameters );

    if( ReqPtr )
       ShmBridgeProtocol->ShmBridgeFree(ShmBridgeProtocol, ReqPtr);

    DEBUG((EFI_D_ERROR, "ScmArmV8ExitBootServicesHandler, Status = 0x%x. \r\n", Status ));

    gBS->RestoreTPL(PrevTPL);

    return Status;
}


/**
  This is called when smc invoke is used.

  @param  Object      *ClientEnvObject
  @retval EFI_STATUS   Status

**/
EFI_STATUS ScmGetClientEnv
(
   IN QCOM_SCM_PROTOCOL   *This,
   OUT VOID               *ClientEnvObject
)
{
#ifdef SMC_INVOKE_SUPPORT

   EFI_STATUS  Status  = EFI_INVALID_PARAMETER;
   EFI_TPL     PrevTPL = 0;

   PrevTPL = gBS->RaiseTPL(TPL_CALLBACK);

   if( ClientEnvObject == NULL )
      goto Exit;

   Status = SmcInvokeGetClientEnv( ( Object *)ClientEnvObject );   
   if( Status )
      DEBUG((EFI_D_ERROR, " SmcInvokeGetClientEnv Falied  Status =  0x%x\r\n",  Status ));

Exit:

    gBS->RestoreTPL(PrevTPL);

    return Status;

#else

   return  EFI_UNSUPPORTED;

#endif //SMC_INVOKE_SUPPORT

}


QCOM_SCM_PROTOCOL QcomScmArmV8ProtocolImpl =
{
   QCOM_SCM_PROTOCOL_REVISION,
   ScmArmV8SysCall,
   ScmArmV8FastCall,
   ScmArmV8GetVersion,
   ScmArmV8RegisterCallback,
   ScmArmV8SendCommand,
   ScmArmV8ExitBootServicesHandler,
   ScmArmV8SipSysCall,
   ScmArmV8DeRegisterCallback,
   ScmGetClientEnv,
   ScmArmV8QseeSysCall
};


BOOLEAN
IsArmV8Smc(VOID)
{
    EFI_STATUS Status;
    UINT64 Parameters[SCM_MAX_NUM_PARAMETERS] = { 0 };
    UINT64 Results[SCM_MAX_NUM_RESULTS] = { 0 };

    Parameters[0] = TZ_INFO_GET_DIAG_ID;

    Status = SysCallInternal( TZ_INFO_IS_SVC_AVAILABLE_ID,
                              TZ_INFO_IS_SVC_AVAILABLE_ID_PARAM_ID,
                              Parameters,
                              Results,
                              NULL );
    if (EFI_ERROR(Status))
    {
        return FALSE;
    }
    else
    {
        return TRUE;
    }
}
