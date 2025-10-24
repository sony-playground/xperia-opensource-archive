/**
  @file EnterpriseMgtVarLock.c
  @brief EnterpriseMgt dxe helper functions to lock UEFI variable.
*/
/*=============================================================================
  Copyright (c) 2020, 2022 Qualcomm Technologies, Incorporated.
  All rights reserved.
  Qualcomm Technologies Inc., Confidential and Proprietary.
=============================================================================*/
/*=============================================================================
 $Header: //components/rel/core.boot/6.1.1/QcomPkg/Drivers/EnterpriseMgtDxe/EnterpriseMgtVarLock.c#1 $
                              EDIT HISTORY


 when          who     what, where, why
 ----------    ---    --------------------------------------------------------
 02/21/2020     hh    Initial version.
=============================================================================*/
#include <Uefi.h>
#include <string.h>
#include <Library/UefiLib.h>
#include <Library/UefiCfgLib.h>
#include <Library/DebugLib.h>
#include <Protocol/VariablePolicy.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/BaseLib.h>
#include <Library/UefiRuntimeServicesTableLib.h>
#include <Protocol/EFIEnterpriseMgt.h>
#include "EnterpriseMgtDxeBaseDef.h"
#include "EnterpriseMgtVarLock.h"

static BOOLEAN isEntMgtUefiVarLockCalled = FALSE;
    
/**
  Function to lock Enterprise Management UEFI Variable.
  
  @retval EFI_SUCCESS          Locked successfully.
  @retval LocateProtocol() or IsVariablePolicyEnabled() or RegisterVariablePolicy() returned err code.

**/
static EFI_STATUS EnterpriseMgtLockUEFIVariable ( VOID )
{
    EFI_STATUS status = EFI_DEVICE_ERROR;
    UINTN BuffSz = 0;
    VARIABLE_POLICY_ENTRY *pLockNowPolicy = NULL;
    VARIABLE_POLICY_PROTOCOL *vp = NULL;
    BOOLEAN State  = FALSE;
    EFI_GUID EnterpriseMgtClientPoliciesGuid = ENT_MGT_CLIENT_POLICIES_GUID;
    
    isEntMgtUefiVarLockCalled = TRUE;

    status = gBS->LocateProtocol(&gVariablePolicyProtocolGuid, NULL, (VOID **)&vp);
    if (EFI_ERROR(status))
    {
        DEBUG((ENT_MGT_ERRO, 
            "EnterpriseMgt : Locate Variable Policy Protocol failed, status = 0x%p\n", status));
        goto Exit;
    }

    status = vp->IsVariablePolicyEnabled(&State);
    if (EFI_ERROR (status) || (State != TRUE))
    {
        DEBUG((ENT_MGT_ERRO, 
            "EnterpriseMgt : FAILED: Variable Policy status = 0x%p State = 0x%x\n", status, State));
        goto Exit;
    }
       
    BuffSz = sizeof(VARIABLE_POLICY_ENTRY) + sizeof(ENT_MGT_CLIENT_POLICIES_NAME);
    
    pLockNowPolicy = (VARIABLE_POLICY_ENTRY *)AllocateZeroPool(BuffSz);
    if (pLockNowPolicy == NULL)
    {
        DEBUG((ENT_MGT_ERRO, "EnterpriseMgt : AllocateZeroPool failed for pLockNowPolicy.\n"));
        goto Exit;
    }
    
    pLockNowPolicy->Version            = VARIABLE_POLICY_ENTRY_REVISION;
    pLockNowPolicy->Size               = BuffSz;
    pLockNowPolicy->OffsetToName       = sizeof(VARIABLE_POLICY_ENTRY);
    pLockNowPolicy->Namespace          = EnterpriseMgtClientPoliciesGuid;
    pLockNowPolicy->MinSize            = 0;
    pLockNowPolicy->MaxSize            = MAX_UINT32;
    pLockNowPolicy->AttributesMustHave = ENT_MGT_CLIENT_POLICIES_ATTR;
    pLockNowPolicy->AttributesCantHave = EFI_VARIABLE_RUNTIME_ACCESS;
    pLockNowPolicy->LockPolicyType     = LockNow;
    
    CopyMem( (UINT8*)pLockNowPolicy + sizeof(VARIABLE_POLICY_ENTRY), 
            ENT_MGT_CLIENT_POLICIES_NAME, 
            sizeof(ENT_MGT_CLIENT_POLICIES_NAME));
    
    status = vp->RegisterVariablePolicy(pLockNowPolicy);
    if (EFI_ERROR(status))
    {
        DEBUG((ENT_MGT_ERRO, 
            "EnterpriseMgt : RegisterVariablePolicy failed, status = 0x%p\n", status));
        goto Exit;
    }
    else
    {
        DEBUG((ENT_MGT_INFO, "EnterpriseMgt : Locked UEFI variable %s successfully.\n", 
            ENT_MGT_CLIENT_POLICIES_NAME));
    }
    
Exit:
  
    if (pLockNowPolicy)
    {
        FreePool(pLockNowPolicy);
        pLockNowPolicy = NULL;
    }
    
    return status;
}

/**
  Protocol function to lock EnterpriseMgt UEFI Variable.

  @retval EFI_SUCCESS          Locked successfully.
  @retval EnterpriseMgtLockUEFIVariable returned value.
**/
EFI_STATUS EnterpriseMgtLockNowVar( VOID )
{
    EFI_STATUS  status = EFI_SUCCESS;
    
    DEBUG((ENT_MGT_INFO, "EnterpriseMgt : Received EnterpriseMgtLockNowVar call \n"));
    if (!isEntMgtUefiVarLockCalled)
    {
        status = EnterpriseMgtLockUEFIVariable();
    }
    else
    {
        DEBUG((ENT_MGT_INFO, "EnterpriseMgt : Lock API was already called. \n"));
    }
    
    return status;
}

/**
  Callback function for Ready to Boot Event.

  @param[in]  Event     Event whose notification function is being invoked
  @param[in]  Context   Pointer to the notification function's context
**/
static VOID EFIAPI EnterpriseMgtOnReadyToBootCallback (
    IN EFI_EVENT Event, 
    IN VOID *Context
    )
{  
    DEBUG((ENT_MGT_INFO, "EnterpriseMgt : Received OnReadyToBoot event Callback \n"));
    
    if (!isEntMgtUefiVarLockCalled)
    {
        EnterpriseMgtLockUEFIVariable();
    }
    else
    {
        DEBUG((ENT_MGT_INFO, "EnterpriseMgt : Lock API was already called. \n"));
    }
}

/**
  Function to register a callback for Ready to Boot Event.

  @retval EFI_SUCCESS           Registered successfully.
  @retval EfiCreateEventReadyToBootEx returned value.
**/
EFI_STATUS EnterpriseMgtRegisterForReadyToBootEvent( VOID )
{
    EFI_STATUS  status = EFI_DEVICE_ERROR;
    EFI_EVENT ReadyToBootEvent = NULL; 

    DEBUG ((ENT_MGT_INFO, "EnterpriseMgt : Registering for OnReadyToBoot event Callback.\n"));
                
    status = EfiCreateEventReadyToBootEx (
               TPL_CALLBACK,
               EnterpriseMgtOnReadyToBootCallback,
               NULL,
               &ReadyToBootEvent
               );

    if (status != EFI_SUCCESS)
    {
        DEBUG((ENT_MGT_ERRO, 
            "EnterpriseMgt : EfiCreateEventReadyToBootEx failed for ReadyToBootEvent. \
            Status = (0x%p)\n", status));
        ASSERT(FALSE);
    }
    
    return status;
}
