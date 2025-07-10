/** @file ScmDxe.c
   
  ScmDxe provides secure channel messaging functions to communicate with Trust Zone.

  Copyright (c) 2012-2019 Copyright Qualcomm Technologies, Inc.  All Rights Reserved.
  Qualcomm Technologies Proprietary and Confidential.
   
**/

/*=============================================================================
                              EDIT HISTORY


 when       who     what, where, why
 --------   ---     -----------------------------------------------------------
 09/19/19   shl     Ported change from Poipu, reorg listener code
 09/11/18   dp      Changed Error message to Warning
 07/14/18   shl     Log message change
 12/22/14   sm      Changed allocation to happen on initialization
 07/16/14   sm      Added two alternative implementations in seperate files
 07/09/14  rp       Raise/RestoreTPL additions to scm fast/slow calls
 06/11/14   sm      Updated to handle APP Shutdown CMD return case
 03/18/14   sm      Updated types and standardized some typecasting
 10/04/13   shl     Added EFI_UNSUPPORTED return for ScmSysCall
 07/25/13   shl     Changed printing level.
 06/19/13   shl     Removed {} to avoid multiple allocation
 05/04/13   sp      Fixed klocwork error
 04/22/13  bmuthuku Send signal to fTPM to disable NV flushing and call ScmExitbootservices 
                    callback from BDS to maintain order of operation for variables flush and
                    listener deregister.
 03/01/13   shl     Added RPMB erase support
 02/22/13   shl     Improve performance by reducing allocation times.
 02/07/13   shl     Added provisioning RPMB support
 02/05/13   ag      Add more commands
 01/28/13   shl     Warning fix 
 12/12/12   shl     Changed the structure due to TZ not supporting flexible header path
 11/17/12   shl     Initial revision

 =============================================================================*/
#include <Uefi.h>
#include <Library/UefiLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiCfgLib.h>
#include <Protocol/EFIScm.h>
#include <Library/QcomLib.h>
#include <Library/DebugLib.h>
#include "tz_syscall.h"
#include "LogBuffer.h"
#include "Listener.h"


// ScmDxe ARMv7 protocol implementation
extern QCOM_SCM_PROTOCOL QcomScmArmV7ProtocolImpl;
extern EFI_STATUS ScmArmV7Initialize(VOID);

// ScmDxe ARMv8 protocol implementation
extern QCOM_SCM_PROTOCOL QcomScmArmV8ProtocolImpl;
extern EFI_STATUS ScmArmV8Initialize(VOID);
extern BOOLEAN IsArmV8Smc(VOID);

// Protocol initialization
EFI_STATUS ScmProtocolInit
(
  IN EFI_HANDLE          ImageHandle,
  IN EFI_SYSTEM_TABLE   *SystemTable
)
{
  EFI_STATUS              Status;
  UINT32                  configFlag = 0;

  if (IsArmV8Smc())
  {
    Status = ScmArmV8Initialize();
    if (Status != EFI_SUCCESS)
        return Status;

    // publish protocol
    Status = gBS->InstallMultipleProtocolInterfaces( &ImageHandle,
                                                     &gQcomScmProtocolGuid,
                                            (VOID **)&QcomScmArmV8ProtocolImpl,
                                                      NULL);  
  }
  else
  {
    Status = ScmArmV7Initialize();
    if (Status != EFI_SUCCESS)
        return Status;

    // publish protocol
    Status = gBS->InstallMultipleProtocolInterfaces( &ImageHandle,
                                                     &gQcomScmProtocolGuid,
                                            (VOID **)&QcomScmArmV7ProtocolImpl,
                                                     NULL);    
  }

  if (Status != EFI_SUCCESS)
    return Status;

  /* Check if qsee logs are enabled (in uefiplat.cfg file) */
  if ((GetConfigValue("SecurityFlag", &configFlag) == EFI_SUCCESS) && (configFlag & ENABLE_QSEE_LOGS_FLAG)) 
  {
    if (QseeRegisterLogBuffer() != EFI_SUCCESS)
       DEBUG ((EFI_D_ERROR, "QseeRegisterLogBuffer: Failed to register log buffer message \n"));
  }

  return Status;
}

