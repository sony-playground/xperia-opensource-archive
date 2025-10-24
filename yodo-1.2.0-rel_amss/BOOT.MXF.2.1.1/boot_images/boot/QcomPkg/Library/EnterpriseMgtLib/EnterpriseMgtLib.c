/**
  @file EnterpriseMgtLib.h
  @brief EnterpriseMgt library functions.
*/
/*=============================================================================
  Copyright (c) 2020 Qualcomm Technologies, Incorporated.
  All rights reserved.
  Qualcomm Technologies Inc., Confidential and Proprietary.
=============================================================================*/
/*=============================================================================
 $Header: //components/rel/core.boot/6.1.1/QcomPkg/Library/EnterpriseMgtLib/EnterpriseMgtLib.c#1 $
                              EDIT HISTORY


 when          who     what, where, why
 ----------    ---    --------------------------------------------------------
 02/21/2020     hh    Initial version.
=============================================================================*/

#include <Uefi.h>
#include <Base.h>
#include <Library/BaseMemoryLib.h>
#include <Library/DebugLib.h>
#include <Library/UefiRuntimeServicesTableLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/QcomLib.h>
#include <Library/BaseLib.h>
#include <Protocol/EFIVariableServices.h>
#include <Protocol/EFIEnterpriseMgt.h>
#include <EnterpriseMgtLib.h>

/**
  Enterprise Management helper function to map features to bits for storing in UEFI NV variable.

  @param[in] NumFeatures  Number of features to disable.
  @param[in] pFeatureList Array pointing to the features to disable.
  @param[out] pStore      Structure for storing the bitmap and checksum values.

  @retval EFI_SUCCESS            Successfully processed the request.
  @retval EFI_INVALID_PARAMETER  Invalid arguments.

**/
static EFI_STATUS EnterpriseMgtMapFeaturesToBits(
    IN UINT16 NumFeatures,
    IN ENT_MGT_FEATURE_TYPE *pFeatureList,
    OUT ENT_MGT_POLICY_STORE *pStore
)
{
    EFI_STATUS status = EFI_SUCCESS;
    UINT16 i = 0;
    UINT32 index = 0;
    UINT32 bit = 0;
    
    if ( NumFeatures == 0 ||
         pFeatureList == NULL ||
         pStore == NULL )
    {
        status = EFI_INVALID_PARAMETER;
        goto Exit;
    }
	
    if (ENT_MGT_MAX_FEATURES > (MAX_FEATURE_BITMAP_SIZE * MAX_NUM_BITS_IN_ENT_MGT_REG))
    {
        DEBUG((ENT_MGT_ERRO, "EnterpriseMgtLib : Max features:%d > BitMap Max size:%d\n", 
            ENT_MGT_MAX_FEATURES, (MAX_FEATURE_BITMAP_SIZE * MAX_NUM_BITS_IN_ENT_MGT_REG)));
        status = EFI_OUT_OF_RESOURCES;
        goto Exit;
    }
	
    if (NumFeatures > (MAX_FEATURE_BITMAP_SIZE * MAX_NUM_BITS_IN_ENT_MGT_REG))
    {
        DEBUG((ENT_MGT_ERRO, "EnterpriseMgtLib : NumFeatures:%d > BitMap Max size:%d\n", 
            NumFeatures, (MAX_FEATURE_BITMAP_SIZE * MAX_NUM_BITS_IN_ENT_MGT_REG)));
        status = EFI_OUT_OF_RESOURCES;
        goto Exit;
    }
    
    pStore->CheckSum = 0; // Initialize to zero first.
    
    for (i = 0; i < NumFeatures; i++)
    {
        index = (pFeatureList[i] / MAX_NUM_BITS_IN_ENT_MGT_REG);
        bit = (pFeatureList[i] % MAX_NUM_BITS_IN_ENT_MGT_REG);
        pStore->FeatureBitMap[index] |= (1 << bit);
    }
    
    pStore->CheckSum = CalculateCheckSum16((UINT16*)pStore, sizeof(ENT_MGT_POLICY_STORE));
	
Exit:
    return status;
}

/**
  Enterprise Management function to store client policies into UEFI NV variable. These policies 
  are used to disable hardware features in enterprise management registers by EnterpriseMgt dxe.

  @param[in] NumFeatures  Number of features to disable.
  @param[in] pFeatureList Array pointing to the features to disable.

  @retval EFI_SUCCESS            Successfully processed requested client policies.
  @retval EFI_INVALID_PARAMETER  Invalid arguments.
  @retval EFI_OUT_OF_RESOURCES   Memory allocation failed for internal usage.
  @retval EFI_DEVICE_ERROR       Internal error while processing requested client policies.
  @retval SetVariable() or FlushVariableServices() returned error code.

**/
EFI_STATUS 
EFIAPI 
EnterpriseMgtSetFeaturesToDisable (
    IN UINT16 NumFeatures, 
    IN ENT_MGT_FEATURE_TYPE *pFeatureList
    )
{
    EFI_STATUS status = EFI_SUCCESS;
    UINT16 i = 0;
    ENT_MGT_POLICY_STORE *pStore = NULL;
    UINTN PolicySize = 0;
    EFI_GUID EnterpriseMgtClientPoliciesGuid = ENT_MGT_CLIENT_POLICIES_GUID;
    
    if (pFeatureList != NULL && NumFeatures != 0)
    {
        DEBUG((ENT_MGT_INFO, 
            "EnterpriseMgtLib : Received %d features to disable.\n", NumFeatures));
        
        if (NumFeatures > ENT_MGT_MAX_FEATURES)
        {
            DEBUG((ENT_MGT_ERRO, "EnterpriseMgtLib : NumFeatures:%d exceeds limit:%d\n", 
                NumFeatures, ENT_MGT_MAX_FEATURES));
            status = EFI_INVALID_PARAMETER;
            goto Exit;
        }
        
        PolicySize = sizeof(ENT_MGT_POLICY_STORE);
        pStore = (ENT_MGT_POLICY_STORE*)AllocateZeroPool( PolicySize );
        if (pStore == NULL)
        {
            DEBUG((ENT_MGT_ERRO, 
                "EnterpriseMgtLib : Memory allocation failed for gpProcessedPolicyStore\n"));
            status = EFI_OUT_OF_RESOURCES;
            goto Exit;
        }
        
        pStore->HeadCookie = HEAD_COOKIE;
        pStore->TailCookie = TAIL_COOKIE;
        pStore->PolicyVersion = ENT_MGT_POLICY_VERSION;
        pStore->NumFeatures = NumFeatures;
        pStore->Reserved = 0;

        for (i = 0; i < NumFeatures; i++)
        {
            if ( pFeatureList[i] >= ENT_MGT_MAX_FEATURES )
            {
                DEBUG((ENT_MGT_ERRO, 
                    "EnterpriseMgtLib : Received invalid feature type %d at index %d.\n", 
                    pFeatureList[i], i));
                status = EFI_INVALID_PARAMETER;
                goto Exit;
            }
        }
        
        status = EnterpriseMgtMapFeaturesToBits(NumFeatures, pFeatureList, pStore);
        if (status != EFI_SUCCESS)
        {
            DEBUG((ENT_MGT_ERRO, "EnterpriseMgtLib : Failed to map features to bitmap. Status = 0x%p\n", status));
            goto Exit;
        }

        DEBUG((ENT_MGT_INFO, "EnterpriseMgtLib : Storing UEFI NV variable : %s of size : %d bytes\n", 
            ENT_MGT_CLIENT_POLICIES_NAME, PolicySize));
        status = gRT->SetVariable(
                        ENT_MGT_CLIENT_POLICIES_NAME, 
                        &EnterpriseMgtClientPoliciesGuid, 
                        ENT_MGT_CLIENT_POLICIES_ATTR, 
                        PolicySize, 
                        pStore
                        );

        if (status != EFI_SUCCESS)
        {
            DEBUG((ENT_MGT_ERRO, "EnterpriseMgtLib : SetVariable failed to store %s. Status = 0x%p\n", 
                ENT_MGT_CLIENT_POLICIES_NAME, status));
            goto Exit;
        }
    }
    else
    {
        DEBUG((ENT_MGT_INFO, 
            "EnterpriseMgtLib : Deleting UEFI NV variable : %s of size : %d bytes\n",
            ENT_MGT_CLIENT_POLICIES_NAME, sizeof(ENT_MGT_POLICY_STORE)));
        status = gRT->SetVariable(
                        ENT_MGT_CLIENT_POLICIES_NAME, 
                        &EnterpriseMgtClientPoliciesGuid, 
                        ENT_MGT_CLIENT_POLICIES_ATTR, 
                        0,
                        NULL
                        );
        status = (status == EFI_NOT_FOUND) ? EFI_SUCCESS : status;
        if (status != EFI_SUCCESS)
        {
            DEBUG((ENT_MGT_ERRO, "EnterpriseMgtLib : SetVariable failed to delete %s. Status = 0x%p\n", 
                ENT_MGT_CLIENT_POLICIES_NAME, status));
            goto Exit;
        }
    }
    
    // Flush the variables so the updated policies are properly stored in UEFI NV store.
    // TODO: Comment out flushing if OEM's guarantee the UEFI NV variable writes to disk.
    // status = FlushVariableServices();
    // if (status != EFI_SUCCESS)
    // {
    //     DEBUG((ENT_MGT_ERRO, 
    //         "EnterpriseMgtLib : Unable to flush NV variables to NV memory. Status = 0x%p\n", 
    //         status));
    //     goto Exit;
    // }
    
Exit:
    // ASSERT_EFI_ERROR(status);
    
    if (pStore)
    {
        FreePool(pStore);
        pStore = NULL;
    }
    
    return status;
}
