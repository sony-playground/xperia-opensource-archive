/**
  @file EnterpriseMgtDxe.c
  @brief EnterpriseMgt dxe driver.
*/
/*=============================================================================
  Copyright (c) 2020 Qualcomm Technologies, Incorporated.
  All rights reserved.
  Qualcomm Technologies Inc., Confidential and Proprietary.
=============================================================================*/
/*=============================================================================
 $Header: //components/rel/core.boot/6.0/QcomPkg/Drivers/EnterpriseMgtDxe/EnterpriseMgtDxe.c#1 $
                              EDIT HISTORY


 when          who     what, where, why
 ----------    ---    --------------------------------------------------------
 02/21/2020     hh    Initial version.
=============================================================================*/
#include <Library/UefiLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/UefiRuntimeServicesTableLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/QcomTargetLib.h>
#include <Library/DebugLib.h>
#include <Library/IoLib.h>
#include <Library/UefiCfgLib.h>
#include <Library/UefiLib.h>
#include <EnterpriseMgtLib.h>
#include <Protocol/EFIEnterpriseMgt.h>
#include "EnterpriseMgtDxeBaseDef.h"
#include "EnterpriseMgtVarLock.h"
#include "EnterpriseMgtCore.h"

EFI_QCOM_ENTERPRISEMGT_PROTOCOL gQcomEnterpriseMgtImpl = 
{
    EnterpriseMgtLockNowVar
};

/**
  Initialize the EnterpriseMgt driver/Hardware registers.

  @param  ImageHandle   of the loaded driver
  @param  SystemTable   Pointer to the System Table

  @retval EFI_SUCCESS           Driver initialized successfully.
  @retval EFI_DEVICE_ERROR      Hardware problems.
  @retval EFI_COMPROMISED_DATA  EnterpriseMgt UEFI variable cookies are corrupted.
  @retval EFI_LOAD_ERROR        Unable to read the valid EnterpriseMgt UEFI NV variable.
  @retval EFI_OUT_OF_RESOURCES  Memory allocation failed.

**/
EFI_STATUS 
EFIAPI 
EnterpriseMgtDxeEntryPoint (
    IN EFI_HANDLE         ImageHandle,
    IN EFI_SYSTEM_TABLE   *SystemTable
    )
{
    EFI_STATUS  status = EFI_DEVICE_ERROR;
    EFI_GUID EnterpriseMgtClientPoliciesGuid = ENT_MGT_CLIENT_POLICIES_GUID;
    UINTN PolicySize = 0;
    UINT32 EnterpriseMgtLockRegAddr = 0;
    UINT32 Attributes = ENT_MGT_CLIENT_POLICIES_ATTR;
    UINT32 EnterpriseMgtSkipVariableLocking = 0;
    ENT_MGT_POLICY_STORE *pStore = NULL;

    status = GetConfigValue ("EnterpriseMgtSkipVariableLocking", &EnterpriseMgtSkipVariableLocking);
    if (status != EFI_SUCCESS)
    {
        EnterpriseMgtSkipVariableLocking = 0; // By default, don't skip variable locking.
    }
    
    status = GetConfigValue ("EnterpriseMgtLockRegAddr", &EnterpriseMgtLockRegAddr);
    if (status != EFI_SUCCESS)
    {
        DEBUG ((ENT_MGT_ERRO, 
            "EnterpriseMgt : Unable to find EnterpriseMgt Lock register address in uefiplat.cfg. \n"));
        goto Exit;
    }
    else
    {  
        if (ENT_MGT_REG_READ(EnterpriseMgtLockRegAddr) & ENT_MGT_LOCK_BIT_POSITION)
        {
            status = EFI_DEVICE_ERROR;
            DEBUG ((ENT_MGT_ERRO, "EnterpriseMgt : Registers are already locked..!!\n"));
            ASSERT(FALSE);
            goto Exit;
        }
        
        PolicySize = sizeof(ENT_MGT_POLICY_STORE);
        pStore = (ENT_MGT_POLICY_STORE *)AllocateZeroPool(PolicySize);
        if (pStore == NULL)
        {
            status = EFI_OUT_OF_RESOURCES;
            DEBUG ((ENT_MGT_ERRO, "EnterpriseMgt : Memory allocation failed for policy store..!!\n"));
            goto Exit;
        }
        
        status = gRT->GetVariable(
                  ENT_MGT_CLIENT_POLICIES_NAME,
                  &EnterpriseMgtClientPoliciesGuid,
                  &Attributes,
                  &PolicySize,
                  pStore);
          
        switch (status)
        {
            case EFI_NOT_FOUND:
                DEBUG ((ENT_MGT_WARN, 
                    "EnterpriseMgt : %s not found.\n", ENT_MGT_CLIENT_POLICIES_NAME));
                
                if (EnterpriseMgtLockRegXBit(EnterpriseMgtLockRegAddr,
                       ENT_MGT_LOCK_BIT_POSITION, 
                       ENT_MGT_LOCK_BIT_VALUE) != TRUE)
                {
                    status = EFI_DEVICE_ERROR;
                    goto Exit;
                }
                else
                {
                    FreePool(pStore);
                    pStore = NULL;
                    status = EFI_SUCCESS;
                }
                break;
                
            case EFI_SUCCESS:
            
                DEBUG ((ENT_MGT_INFO, 
                    "EnterpriseMgt : %s found with Policy Version : 0x%x.\n", 
                    ENT_MGT_CLIENT_POLICIES_NAME, pStore->PolicyVersion));
                
                if ( (pStore->HeadCookie != HEAD_COOKIE) || (pStore->TailCookie != TAIL_COOKIE) )
                {
                    status = EFI_COMPROMISED_DATA;
                    DEBUG ((ENT_MGT_ERRO, 
                        "EnterpriseMgt : Corrupted cookies found in UEFI NV variable %s!!\n", 
                        ENT_MGT_CLIENT_POLICIES_NAME));
                    goto Exit;
                }
                              
                if (PolicySize != sizeof(ENT_MGT_POLICY_STORE))
                {
                    status = EFI_LOAD_ERROR;
                    DEBUG ((ENT_MGT_ERRO, 
                        "EnterpriseMgt : Mismatch in size of UEFI NV variable %s.\n", 
                        ENT_MGT_CLIENT_POLICIES_NAME));
                    goto Exit;
                }
                
                status = EnterpriseMgtProcessClientPolicies(pStore, EnterpriseMgtLockRegAddr);
                if (status != EFI_SUCCESS)
                {
                    DEBUG ((ENT_MGT_ERRO, "EnterpriseMgt : EnterpriseMgtProcessClientPolicies failed.\n"));
                    goto Exit;
                }
                break;
                
            default:
                DEBUG ((ENT_MGT_ERRO, 
                    "EnterpriseMgt : Error 0x%p while reading EnterpriseMgt UEFI NV variable %s.\n",
                    status, ENT_MGT_CLIENT_POLICIES_NAME));
                goto Exit;
                break;
        }
        
        /* 
           RETAIL flag will be TRUE if the build is compiled in RELEASE mode or device debug disable 
           fuses are blown. We would like to lock UEFI NV variable on the retail builds by default
           irrespective of Skip variable status.
           EnterpriseMgtSkipVariableLocking = TRUE will be used to skip UEFI NV locking on debug builds.
        */
        if (EnterpriseMgtSkipVariableLocking == 0 || RETAIL)
        {
            if (EnterpriseMgtRegisterForReadyToBootEvent() != EFI_SUCCESS)
            {
                DEBUG ((ENT_MGT_ERRO, "EnterpriseMgt : Register for OnReadyToBoot event failed.\n"));
                goto Exit;
            }
        }
        else
        {
            DEBUG ((ENT_MGT_WARN, "EnterpriseMgt : Skipped locking UEFI variable : %s.\n", 
                ENT_MGT_CLIENT_POLICIES_NAME));
        }
        
        // Install EnterpriseMgt protocol
        status = gBS->InstallMultipleProtocolInterfaces (
                            &ImageHandle,
                            &gQcomEnterpriseMgtProtocolGuid,
                            (void **)&gQcomEnterpriseMgtImpl,
                             NULL
                          );
        if (EFI_ERROR (status))
        {
            DEBUG(( ENT_MGT_ERRO, "EnterpriseMgt: Install Protocol failed, Status = (0x%p)\r\n", status));
            goto Exit;
        }
    }
    
Exit:
    // ASSERT_EFI_ERROR(status);
    
    if (EFI_ERROR (status))
    {
        DEBUG(( ENT_MGT_ERRO, "EnterpriseMgt: Failed with status = (0x%p). Uninstalling protocol.\r\n", status));
        gBS->UninstallMultipleProtocolInterfaces (
                        ImageHandle,
                        &gQcomEnterpriseMgtProtocolGuid,
                        (void **)&gQcomEnterpriseMgtImpl,
                        NULL
                        );
    }
     
    if (pStore)
    {
        FreePool(pStore);
        pStore = NULL;
    }
    
    return status;
}