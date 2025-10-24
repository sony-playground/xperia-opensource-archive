/** 
  file  EFIScm.h
  
  Secure Messaging Channel Protocol for UEFI.

*/
/*=============================================================================
   Copyright (c) 2012-2014, 2018-2020, Qualcomm Technologies, Inc.
   All Rights Reserved. Qualcomm Technologies Proprietary and Confidential.

=============================================================================*/

/*=============================================================================
                              EDIT HISTORY


 when       who     what, where, why
 --------   ---     -----------------------------------------------------------
 10/08/20   shl      Added a New API for handling listener request
 11/18/19   shl      Added GetClientEnvObj API to support SMC invoke
 09/19/19   shl      Split listener structure to be an independent file
 09/27/18   pj       Updates to enable loading of TZ-embedded common libs and tpm TA
 08/15/14   sm       Added new SCM API
 03/18/14   sm       Updated length types
 11/20/13   llg      (Tech Pubs) Edited function syntax; otherwise, Doxygen will not run
 06/18/13   llg      (Tech Pubs) Edited/added Doxygen comments and markup.
 04/22/13  bmuthuku  Send signal to fTPM to disable NV flushing and call ScmExitbootservices 
					                callback from BDS to maintain order of operation for variables flush 
                     and listener deregister. Expose callback.
 02/01/13   shl      Added more comments and new command
 02/07/13   shl      Added support for RPMB provisioning
 11/16/12   shl      Initial version
=============================================================================*/
#ifndef __EFISCM_H__
#define __EFISCM_H__

/*===========================================================================
  INCLUDE FILES
===========================================================================*/
#include <Uefi.h>
#include "EFIListenerDef.h"

/** @defgroup QCOM_SCM_PROTOCOL  QCOM_SCM_PROTOCOL 
 *  @ingroup SECURITY 
 */
 /** @defgroup  QCOM_SCM_PROTOCOL_prot PROTOCOL
 *  @ingroup QCOM_SCM_PROTOCOL 
 */ 
 /** @defgroup  QCOM_SCM_PROTOCOL_apis APIs
 *  @ingroup QCOM_SCM_PROTOCOL 
 */ 

/** @defgroup  QCOM_SCM_PROTOCOL_data DATA_STRUCTURES
 *  @ingroup QCOM_SCM_PROTOCOL 
 */

/*===========================================================================
  MACRO DECLARATIONS
===========================================================================*/
/** @ingroup QCOM_SCM_PROTOCOL_data
  Protocol version.
*/
#define QCOM_SCM_PROTOCOL_REVISION 0x0000000000040001

/*===========================================================================
  EXTERNAL VARIABLES
===========================================================================*/
/** @ingroup QCOM_SCM_PROTOCOL_data */
extern EFI_GUID gQcomScmProtocolGuid;

/*===========================================================================
  TYPE DEFINITIONS
===========================================================================*/

/** @ingroup QCOM_SCM_PROTOCOL_data
  Commands supported by TrustZone QSEE (Qualcomm Secure Execution Environment) 
  structures.
*/
typedef enum
{
  APP_START_APP_CMD = 0x01,              /**< Start application. */
  APP_SHUTDOWN_CMD,                      /**< Shut down. */
  APP_QUERY_APPID_CMD,                   /**< Query application ID. */
  APP_REGISTER_LISTENER_CMD,             /**< Register listener. */
  APP_DEREGISTER_LISTENER_CMD,           /**< Deregister listener. */
  APP_SEND_DATA_CMD,                     /**< Send data. */
  APP_LISTENER_DATA_RSP_CMD,             /**< Listener data response. */
  APP_LOAD_EXTERNAL_ELF_CMD,             /**< Load external ELF. */
  APP_UNLOAD_EXTERNAL_ELF_CMD,           /**< Unload external ELF. */
  APP_GET_APP_STATE_CMD,                 /**< Get application state. */
  APP_LOAD_SERV_IMAGE_CMD,               /**< Load server image. */
  APP_UNLOAD_SERV_IMAGE_CMD,             /**< Unload server image. */
  APP_REGION_NOTIFICATION_CMD,           /**< Region notification. */
  APP_REGISTER_LOG_BUF_COMMAND,          /**< Register log buffer. */
  APP_PROVISION_RPMB_KEY_COMMAND,        /**< Provision RPMB key. */
  APP_RPMB_ERASE_COMMAND,                /**< Erase RPMB. */
  APP_RPMB_CHECK_PROV_STATUS_COMMAND,    /**< Checks the RPMB provisioning status. */ 
  APP_QUERY_EMBEDDED_IMAGES_SUPPORT_CMD, /**< Queries embedded images support and loads commonlibs. */ 
  APP_START_EMBEDDED_APP_CMD,            /**< Starts an embedded trusted app. */
  APP_START_TZTESTEXEC_APP_CMD           /**< Starts tzt test app. */

}AppCmdType;

#define SCM_MAX_NUM_PARAMETERS           10
#define SCM_MAX_NUM_RESULTS              4

/** @cond */
/* Protocol declaration.  */
typedef struct _QCOM_SCM_PROTOCOL QCOM_SCM_PROTOCOL;
/** @endcond */

/*===========================================================================
  FUNCTION DEFINITIONS
===========================================================================*/
/* QCOM_SCM_SYS_CALL */ 
/** @ingroup QCOM_SCM_PROTOCOL_apis
  @par Summary
  Slow call into TrustZone.
   
  @param[in]     This  Pointer to the QCOM_SCM_PROTOCOL instance.
  @param[in,out] Cmd   Command data pointer passed into TrustZone.

  @return
  EFI_SUCCESS  -- Function completed successfully. \n
  Other values -- Failure.
*/

typedef
EFI_STATUS
(EFIAPI *QCOM_SCM_SYS_CALL )(
  IN     QCOM_SCM_PROTOCOL      *This, 
  IN OUT const VOID             *Cmd
);

/* QCOM_SCM_SIP_SYS_CALL */ 
/** @ingroup QCOM_SCM_PROTOCOL_apis
  @par Summary
  Slow call into TrustZone. This API will not handle listener request from TZ.
   
  @param[in]     This       Pointer to the QCOM_SCM_PROTOCOL instance.
  @param[in]     SmcId      Function ID for the TZ SIP Syscall to be made.
  @param[in]     ParamId    Parameter ID for TZ SIP Syscall.
  @param[in]     Parameters Parameters struct for TZ SIP Sycall.
  @param[out]    Results    Result struct from TZ SIP Syscall.

  @return
  EFI_SUCCESS  -- Function completed successfully. \n
  Other values -- Failure.
*/

typedef
EFI_STATUS 
(EFIAPI *QCOM_SCM_SIP_SYS_CALL)(
  IN  QCOM_SCM_PROTOCOL   *This, 
  IN  UINT32               SmcId,
  IN  UINT32               ParamId,
  IN  UINT64               Parameters[SCM_MAX_NUM_PARAMETERS],
  OUT UINT64               Results[SCM_MAX_NUM_RESULTS]
);

/* QCOM_SCM_FAST_CALL_2 */ 
/** @ingroup QCOM_SCM_PROTOCOL_apis
  @par Summary
  Fast call with two parameters.

  @param[in]  This    Pointer to the QCOM_SCM_PROTOCOL instance.
  @param[in]  Id      Token ID.
  @param[in]  Param0  Parameter 0.
  @param[in]  Param1  Parameter 1.
   
  @return
  EFI_SUCCESS  -- Function completed successfully. \n
  Other values -- Failure.
*/
typedef
EFI_STATUS 
(EFIAPI *QCOM_SCM_FAST_CALL_2)(
  IN QCOM_SCM_PROTOCOL      *This, 
  IN UINT32                  Id,
  IN UINT32                  Param0,
  IN UINT32                  Param1
);

/* QCOM_SCM_GET_VERSION */
/** @ingroup QCOM_SCM_PROTOCOL_apis
  @par Summary
  Calls into TrustZone to get the TrustZone version.
   
  @param[in]     This     Pointer to the QCOM_SCM_PROTOCOL instance.
  @param[in,out] Version  Pointer to the TrustZone version address.

  @return
  EFI_SUCCESS  -- Function completed successfully. \n
  Other values -- Failure.
*/
typedef
EFI_STATUS
(EFIAPI *QCOM_SCM_GET_VERSION)(
  IN     QCOM_SCM_PROTOCOL         *This, 
  IN OUT UINT32                    *Version
);

/* QCOM_SCM_SEND_COMMAND */
/* This is designed to fit the new TZ 1.4 interface structures. 
   Here is how it is used:

  APP_START_APP_CMD            AppId = NULL, Req = &(Your request), Rsp=NULL
  APP_SHUTDOWN_CMD             AppId =&(Your AppID), Req = NULL, Rsp = NULL 
  APP_QUERY_APPID_CMD          AppId==&(Your AppID), Req = &(your ascii app name string), Rsp=NULL
  APP_REGISTER_LISTENER_CMD    separate interface
  APP_DEREGISTER_LISTENER_CMD  handled internally
  APP_SEND_DATA_CMD            AppId =&(Your AppID), Req = &(Your request), Rsp =&(your response) 
  APP_LISTENER_DATA_RSP_CMD    handled internally
  APP_PROVISION_RPMB_KEY_COMMAND   AppId=NULL  ,Req=&(your key_type), Rsp !=NULL RspLen >=4
  APP_PROVISION_RPMB_KEY_COMMAND   AppId=NULL  ,Req=NULL, ReqLen = 0, Rsp !=NULL RspLen >=4
*/
/** @ingroup QCOM_SCM_PROTOCOL_apis
  @par Summary
  Interface for sending a command to the SCM DXE. 

  @param[in]     This    Pointer to the QCOM_SCM_PROTOCOL instance.
  @param[in]     CmdId   Command type; see #AppCmdType for details.
  @param[in]     AppId   Pointer to the application ID.
  @param[in,out] Req     Request pointer.
  @param[in]     ReqLen  Request data length in bytes.
  @param[in,out] Rsp     Response pointer.
  @param[in]     RspLen  Response data length in bytes.

  @par Description
  The following describes how this function is used:
  - APP_START_APP_CMD
@vertspace{3}
@code
AppId = NULL, Req = &(Your request), Rsp=NULL
@endcode
  - APP_SHUTDOWN_CMD
@vertspace{3}
@code
AppId =&(Your AppID), Req = NULL, Rsp = NULL 
@endcode
  - APP_QUERY_APPID_CMD
@vertspace{3}
@code
AppId==&(Your AppID), Req = &(Your ascii app name string), Rsp=NULL
@endcode
  - APP_REGISTER_LISTENER_CMD -- Separate interface
  - APP_DEREGISTER_LISTENER_CMD -- Handled internally
  - APP_SEND_DATA_CMD
@vertspace{3}
@code
AppId =&(Your AppID), Req = &(Your request), Rsp =&(your response) 
@endcode
  - APP_LISTENER_DATA_RSP_CMD -- Handled internally
  - APP_PROVISION_RPMB_KEY_COMMAND
@vertspace{3}
@code
AppId=NULL  ,Req=&(your key_type), Rsp !=NULL RspLen >=4
@endcode
  - APP_RPMB_ERASE_COMMAND
@vertspace{3}
@code
AppId=NULL  ,Req=NULL, ReqLen = 0, Rsp !=NULL RspLen >=4
@endcode

  @return
  EFI_SUCCESS  -- Function completed successfully. \n
  Other values -- Failure.
*/
typedef
EFI_STATUS
(EFIAPI *QCOM_SCM_SEND_COMMAND)(
  IN     QCOM_SCM_PROTOCOL      *This, 
  IN     AppCmdType              CmdId, 
  IN     UINT32                 *AppId,
  IN OUT VOID                   *Req,
  IN     UINTN                   ReqLen,
  IN OUT VOID                   *Rsp,
  IN     UINTN                   RspLen
);


/* QCOM_SCM_REGISTER_CALLBACK */
/** @ingroup QCOM_SCM_PROTOCOL_apis
  @par Summary
  Calls TrustZone to register a callback function or SMC invoke callback
  message length. 
  The SCM DXE also keeps a record of this registration.
   
  @param[in]  This             Pointer to the QCOM_SCM_PROTOCOL instance.
  @param[in]   ListenerID         Listener ID.
  @param[in]  CallbackPtr      Pointer to the callback function.
  @param[in]  CallbackHandle   Handle pointer from the caller.
  @param[in]  SharedBufferPtr  Pointer to the shared buffer.
  @param[in]  SharedBufferLen  Length of the shared buffer.

  Special case:
  if param[in]  ListenerId      == 0     && 
                CallbackPtr     == NULL  &&
                CallbackHandle  == NULL  &&
                SharedBufferPtr == NULL  &&
                SharedBufferLen != 0
  then this is used for set the SMC invoke callback message length. 

  It is expected that client knows which their mink calls can trigger callback and how
  much buffer should be allocated for each such callback call.
  
  If the total buffer length is more than 3K bytes, this funstion must be called
  to set the total buffer length. Total buffer length means the sum of all buffer
  length parameters passed into a mink call. For cases less than 3K bytes, no need
  to call this function.   

  The maximum value can be set is 0x80000.

  Total buffer length set in this function call has lifetime of its immediately
  followed mink API call. After its immediate mink call, the total buffer length is 
  set to 0 by ScmDxe to avoid miss use. To prevent the multithread disturbation, it is
  suggested to use this way:

     EFI_TPL PrevTPL = gBS->RaiseTPL(TPL_CALLBACK);
     // set the length  
     Status = ScmProtocol->ScmRegisterCallback( ScmProtocol,
                                                0,
                                                NULL,
                                                NULL,
                                                NULL,
                                                TotalBufferLen);
     // TotalBufferLen (= B1Len + B2Len) is set,  it is consumed in the following call
     ret = ITestCBack_callWithBuffer(objTestCallback, B1, B1Len B2, B2Len, objCb_0);
     // TatalBufferLen is set to 0 by ScmDxe by this point

     gBS->RestoreTPL(PrevTPL);

  @return
  EFI_SUCCESS  -- Function completed successfully. \n
  Other values -- Failure.
*/

typedef  
EFI_STATUS
(EFIAPI * QCOM_SCM_REGISTER_CALLBACK)(
  IN QCOM_SCM_PROTOCOL             *This,
  IN UINT32                         ListenerID,
  IN QcomScmListenerCallbackPtr     CallbackPtr,
  IN VOID                          *CallbackHandle,
  IN UINT8                         *SharedBufferPtr,
  IN UINTN                          SharedBufferLen
);

/* QCOM_SCM_DEREGISTER_CALLBACK */
/** @ingroup QCOM_SCM_PROTOCOL_apis
  @par Summary
  Calls TrustZone to deregister a callback function. 
  The SCM DXE also delete record of this registration.
   
  @param[in]  This             Pointer to the QCOM_SCM_PROTOCOL instance.
  @param[in]  ListenerID       Listener ID.

  @return
  EFI_SUCCESS  -- Function completed successfully. \n
  Other values -- Failure.
*/

typedef  
EFI_STATUS
(EFIAPI * QCOM_SCM_DEREGISTER_CALLBACK)(
  IN QCOM_SCM_PROTOCOL           *This,
  IN UINT32                       ListenerID
);

/* QCOM_SCM_EXIT_BOOT_SERVICES */
/** @ingroup QCOM_SCM_PROTOCOL_apis
  @par Summary
  Callback registered for ExitBootServices.

  @param[in]  This  Pointer to the QCOM_SCM_PROTOCOL instance.

  @return
  EFI_SUCCESS  -- Function completed successfully. \n
  Other values -- Failure.
*/
typedef
EFI_STATUS
(EFIAPI *QCOM_SCM_EXIT_BOOT_SERVICES)(
  IN     QCOM_SCM_PROTOCOL         *This  
);

/* QCOM_SCM_GET_CLIENT_ENV */
/** @ingroup QCOM_SCM_PROTOCOL_apis
  @par Summary
  Called when SMC invoke service is used.

  @param[in]      This  Pointer to the QCOM_SCM_PROTOCOL instance.
  @param[in/out]  Pointer to client object acquired, the caller needs
                  to cast it to Object type when using it. object is 
                  defined in QcomPkg/Include objecg.h. Abstract pointer
                  to comply with UEIF protocol folder restriction.

  @return
  EFI_SUCCESS  -- Function completed successfully. \n
  Other values -- Failure.
*/
typedef
EFI_STATUS
(EFIAPI * QCOM_SCM_GET_CLIENT_ENV)(
  IN  QCOM_SCM_PROTOCOL      *This,
  OUT VOID                   *ClientEnvObject
);


/* QCOM_SCM_QSEE_SYS_CALL */ 
/** @ingroup QCOM_SCM_PROTOCOL_apis
  @par Summary
  Slow call into TrustZone. This API should be used if the syscall owner are:
    TZ_OWNER_TZ_APPS   48
    TZ_OWNER_QSEE_OS   50
  This API will handle listener request from TZ.
   
  @param[in]     This       Pointer to the QCOM_SCM_PROTOCOL instance.
  @param[in]     SmcId      Function ID for the TZ SIP Syscall to be made.
  @param[in]     ParamId    Parameter ID for TZ SIP Syscall.
  @param[in]     Parameters Parameters struct for TZ SIP Sycall.
  @param[out]    Results    Result struct from TZ SIP Syscall.

  @return
  EFI_SUCCESS  -- Function completed successfully. \n
  Other values -- Failure.
*/
typedef
EFI_STATUS
(EFIAPI *QCOM_SCM_QSEE_SYS_CALL)(
  IN  QCOM_SCM_PROTOCOL      *This, 
  IN  UINT32                  SmcId,
  IN  UINT32                  ParamId,
  IN  UINT64                  Parameters[SCM_MAX_NUM_PARAMETERS],
  OUT UINT64                  Results[SCM_MAX_NUM_RESULTS]
);

/*===========================================================================
  PROTOCOL INTERFACE
===========================================================================*/
/** @ingroup QCOM_SCM_PROTOCOL_prot
  @par Summary
  Qualcomm Secure Channel Messaging (SCM) Protocol interface.

  @par Parameters
  @inputprotoparams{scm_proto_params.tex} 
*/
struct _QCOM_SCM_PROTOCOL {
  UINT64                         Revision;
  QCOM_SCM_SYS_CALL              ScmSysCall;
  QCOM_SCM_FAST_CALL_2           ScmFastCall2;
  QCOM_SCM_GET_VERSION           ScmGetVersion;
  QCOM_SCM_REGISTER_CALLBACK     ScmRegisterCallback;
  QCOM_SCM_SEND_COMMAND          ScmSendCommand;
  QCOM_SCM_EXIT_BOOT_SERVICES    ScmExitBootServicesHandler;
  QCOM_SCM_SIP_SYS_CALL          ScmSipSysCall;
  QCOM_SCM_DEREGISTER_CALLBACK   ScmDeRegisterCallback;
  QCOM_SCM_GET_CLIENT_ENV        ScmGetClientEnv;
  QCOM_SCM_QSEE_SYS_CALL         ScmQseeSysCall; 
};

#endif /* __EFISCM_H__ */


