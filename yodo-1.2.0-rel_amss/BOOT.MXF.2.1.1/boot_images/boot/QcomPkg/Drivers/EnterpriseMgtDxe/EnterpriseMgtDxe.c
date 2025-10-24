/**
  @file EnterpriseMgtDxe.c
  @brief EnterpriseMgt dxe driver.
*/
/*=============================================================================
  Copyright (c) 2020,2022 Qualcomm Technologies, Incorporated.
  All rights reserved.
  Qualcomm Technologies Inc., Confidential and Proprietary.
=============================================================================*/
/*=============================================================================
 $Header: //components/rel/core.boot/6.1.1/QcomPkg/Drivers/EnterpriseMgtDxe/EnterpriseMgtDxe.c#1 $
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
#include <Library/FuseControlLib.h>
#include <EnterpriseMgtLib.h>
#include <Protocol/EFIEnterpriseMgt.h>
#include <Library/EnterpriseMgtTargetConfigLib.h>
#include <Library/QcomLib.h>
#include <EnterpriseMgtLib.h>
#include "EnterpriseMgtDxeBaseDef.h"
#include "EnterpriseMgtVarLock.h"
#include "EnterpriseMgtCore.h"

EFI_QCOM_ENTERPRISEMGT_PROTOCOL gQcomEnterpriseMgtImpl = 
{
    EFI_QCOM_ENTERPRISEMGT_PROTOCOL_V1,
    EnterpriseMgtLockNowVar
};

/* 
    Emergency recovery mode flag. If the bad policies are pushed to the device causing boot crash, 
    from T32, override this flag to TRUE for clearning the enterprisemgt policies fully. 
*/
BOOLEAN bEntpMgtEmergencyRecoveryMode = FALSE;

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
    ENT_MGT_POLICY_STORE *pStore = NULL;

    /* 
       Use Emergency Recovery mode flag to delete the enterprise management policies fully on debug builds. 
       This will be useful in the case where user pushed the invalid policies causing the boot crash and need 
       an option to recover by deleting the policies explicitly.
    */
    if (bEntpMgtEmergencyRecoveryMode)
    {
        DEBUG((ENT_MGT_WARN, "EnterpriseMgt : Recovery flag set to clear all the policies..!!"));

        EnterpriseMgtSetFeaturesToDisable(0, NULL);

        status = FlushVariableServices();
        if (status != EFI_SUCCESS)
        {
            DEBUG((ENT_MGT_ERRO, "EnterpriseMgt : Unable to flush variables to NV memory. Status = 0x%p\n", 
                status));
        }
    }
	
    EnterpriseMgtLockRegAddr = EnterpriseMgtGetLockRegAddress();
    if (EnterpriseMgtLockRegAddr == 0)
    {
        status = EFI_DEVICE_ERROR;
        DEBUG ((ENT_MGT_ERRO, 
            "EnterpriseMgt : EnterpriseMgtGetLockRegAddress() failed to return valid lock reg address.\n"));
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

                FreePool(pStore);
                pStore = NULL;
                status = EFI_SUCCESS;
                break;
                
            case EFI_SUCCESS:
            
                DEBUG ((ENT_MGT_INFO, 
                    "EnterpriseMgt : %s found with Policy Version : 0x%x of size : 0x%x bytes.\n", 
                    ENT_MGT_CLIENT_POLICIES_NAME, pStore->PolicyVersion, PolicySize));
                
                if (PolicySize != sizeof(ENT_MGT_POLICY_STORE))
                {
                    status = EFI_LOAD_ERROR;
                    DEBUG ((ENT_MGT_ERRO, 
                        "EnterpriseMgt : Mismatch in size(0x%x != 0x%x) of UEFI NV variable %s.\n", 
                        PolicySize, sizeof(ENT_MGT_POLICY_STORE), ENT_MGT_CLIENT_POLICIES_NAME));
                    DEBUG ((ENT_MGT_ERRO, "EnterpriseMgt : Clear UEFI NV variable and push new policies again.\n"));
                    goto Exit;
                }
				
                if ( (pStore->HeadCookie != HEAD_COOKIE) || (pStore->TailCookie != TAIL_COOKIE) )
                {
                    status = EFI_COMPROMISED_DATA;
                    DEBUG ((ENT_MGT_ERRO, 
                        "EnterpriseMgt : Corrupted cookies found in UEFI NV variable %s!!\n", 
                        ENT_MGT_CLIENT_POLICIES_NAME));
                    goto Exit;
                }
                
                status = EnterpriseMgtProcessClientPolicies(pStore);
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

                break;
        }
        
        if (EnterpriseMgtLockRegXBit(EnterpriseMgtLockRegAddr,
               ENT_MGT_LOCK_BIT_POSITION, 
               ENT_MGT_LOCK_BIT_VALUE) != TRUE)
        {
            status = EFI_DEVICE_ERROR;
            DEBUG ((ENT_MGT_ERRO, "EnterpriseMgt : Error : Unable to lock register: 0x%x \n",
                EnterpriseMgtLockRegAddr));
            goto Exit;
        }
		
        /* 
           We would like to lock UEFI NV variable on the retail builds/fuse blown devices by default:
             * RETAIL flag will be TRUE if the build is compiled in RELEASE mode or 
             * Device debug disable fuses are blown in DEBUG mode builds.
           JTAGDebugDisableFusesBlown() returns TRUE when debug fuses are blown.
        */
        if (JTAGDebugDisableFusesBlown() == TRUE || RETAIL)
        {
            status = EnterpriseMgtRegisterForReadyToBootEvent();
            if (status != EFI_SUCCESS)
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
        
        status = EnterpriseMgtPostLockBitCalls();
        if (status != EFI_SUCCESS)
        {
            DEBUG ((ENT_MGT_ERRO, "EnterpriseMgt : EnterpriseMgtPostLockBitCalls failed.\n"));
            goto Exit;
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
