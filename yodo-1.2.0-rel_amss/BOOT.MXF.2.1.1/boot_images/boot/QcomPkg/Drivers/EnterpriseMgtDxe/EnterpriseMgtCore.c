/**
  @file EnterpriseMgtCore.c
  @brief EnterpriseMgt core functions.
*/
/*=============================================================================
  Copyright (c) 2020-2022 Qualcomm Technologies, Incorporated.
  All rights reserved.
  Qualcomm Technologies Inc., Confidential and Proprietary.
=============================================================================*/
/*=============================================================================
 $Header: //components/rel/core.boot/6.1.1/QcomPkg/Drivers/EnterpriseMgtDxe/EnterpriseMgtCore.c#1 $
                              EDIT HISTORY


 when          who     what, where, why
 ----------    ---    --------------------------------------------------------
 02/21/2020     hh    Initial version.
=============================================================================*/

#include <Uefi.h>
#include <Base.h>
#include <string.h>
#include <Library/BaseMemoryLib.h>
#include <Library/DebugLib.h>
#include <Library/UefiRuntimeServicesTableLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/MemoryAllocationLib.h>
#include <EnterpriseMgtLib.h>
#include <Library/QcomLib.h>
#include <Library/BaseLib.h>
#include <Protocol/EFIVariableServices.h>
#include <Protocol/EFIEnterpriseMgt.h>
#include <Library/EnterpriseMgtTargetConfigLib.h>
#include "EnterpriseMgtDxeBaseDef.h"
#include "EnterpriseMgtCore.h"
#include "EnterpriseMgtAcpiPatch.h"

/**
  Helper function to program EnterpriseMgtX registers.

  @param  RegisterAddress   EnterpriseMgtX register address.
  @param  BitMask           EnterpriseMgtX bitmask to program.
  @param  Value             EnterpriseMgtX bit values to program.

  @retval TRUE              EnterpriseMgt register programmed successfully.
  @retval FALSE             EnterpriseMgt register programming failed.
**/
static BOOLEAN EnterpriseMgtWriteToMgtRegister (
    IN UINT32 RegisterAddress, 
    IN UINT32 Mask, 
    IN UINT32 Value
    )
{
    BOOLEAN status = TRUE;
    UINT32 RegReadValue = 0;
    UINT32 FinalValue = 0;

    if (RegisterAddress == 0)
    {
        status = FALSE;
    }
    else
    {
        RegReadValue = ENT_MGT_REG_READ(RegisterAddress);
        FinalValue = (RegReadValue & (~Mask)) | (Mask & Value);
	    
        DEBUG ((ENT_MGT_INFO, 
            "EnterpriseMgt : RegisterAddress: 0x%08x Mask: 0x%08x Value: 0x%08x RegReadValue: 0x%08x FinalValue: 0x%08x \n", 
            RegisterAddress, Mask, Value, RegReadValue, FinalValue));
        
        ENT_MGT_REG_WRITE(RegisterAddress, FinalValue);
        
        if (ENT_MGT_REG_READ(RegisterAddress) != FinalValue)
        {
            status = FALSE;
            DEBUG ((ENT_MGT_ERRO, 
                "EnterpriseMgt : Unable to write to register 0x%08x with value 0x%08x \n", 
                RegisterAddress, FinalValue));
            ASSERT(FALSE);
        }
    }

    return status;
}

/**
  Helper function to program EnterpriseMgtX registers.

  @param  pStore   EnterpriseMgt processed store value read from UEFI NV variable.

  @retval TRUE              EnterpriseMgtX registers programmed successfully.
  @retval FALSE             EnterpriseMgtX register programming failed.
**/
static BOOLEAN EnterpriseMgtWriteToRegX (
    IN ENT_MGT_PROCESSED_POLICY* pStore
    )
{
    BOOLEAN status = TRUE;
    UINT32 i = 0;
    
    for (i = 0; i < pStore->NumMgtXRegs; i++)
    {
        status = EnterpriseMgtWriteToMgtRegister(pStore->MgtXRegList[i].RegisterAddress, 
                                  pStore->MgtXRegList[i].BitMask, 
                                  pStore->MgtXRegList[i].Value);
        if (status != TRUE)
        {
            DEBUG ((ENT_MGT_ERRO, 
                "EnterpriseMgt : Error writing to register: 0x%x , BitMask: 0x%x , Value: 0x%x\n",
                 pStore->MgtXRegList[i].RegisterAddress, pStore->MgtXRegList[i].BitMask, 
                 pStore->MgtXRegList[i].Value));
            break;
        }
    }
    
    return status;
}

/**
  Helper function to program EnterpriseMgt LOCK registers.

  @param  RegisterAddress   EnterpriseMgt LOCK register address.
  @param  BitMask           EnterpriseMgt LOCK bitmask to program.
  @param  Value             EnterpriseMgt LOCK register bit value to program.

  @retval TRUE              EnterpriseMgt LOCK register programmed successfully.
  @retval FALSE             EnterpriseMgt LOCK register programming failed.
**/
BOOLEAN EnterpriseMgtLockRegXBit (
    IN UINT32 RegisterAddress, 
    IN UINT32 BitMask, 
    IN UINT32 Value
    )
{
    BOOLEAN status = TRUE;

    status = EnterpriseMgtWriteToMgtRegister(RegisterAddress, BitMask, Value);
    if (status != TRUE)
    {
        DEBUG ((ENT_MGT_ERRO, "EnterpriseMgt : Unable to lock EnterpriseMgtX registers!!\n"));
    }
    else
    {
        DEBUG ((ENT_MGT_MSGI, "EnterpriseMgt : Locked all EnterpriseMgtX registers.\n"));
    }
 
    return status;
}

/**
  Helper function to accumulate ACPI device node name from the given interface node.

  @param[in] pInterfacenode  Pointer to Interface node.
  @param[in, out] pPolicy     Buffer to store processed information.
  @param[in] Enable          Status to set for the given ACPI device node.

  @retval TRUE  Successfully processed the request.
  @retval FALSE Failed to process this request.
**/
static BOOLEAN EnterpriseMgtUpdateDeviceList (
    IN INTERFACE_NODE* pInterfacenode, 
    IN OUT ENT_MGT_PROCESSED_POLICY* pPolicy, 
    IN BOOLEAN Enable
    )
{
    BOOLEAN status = TRUE;
    BOOLEAN Found = FALSE;
    HLOS_MNG_DEVICE *pDeviceList = NULL;
    UINT32 j = 0;
    UINT32 k = 0;
    
    pDeviceList = (HLOS_MNG_DEVICE*)((char*)pInterfacenode + pInterfacenode->HlosManagedDeviceOffset);

    for (j = 0; j < pInterfacenode->NumberOfHlosManagedDevices; j++)
    {              
        if (sizeof(pDeviceList->DeviceName) > MAX_DEVICE_NAME_SIZE )
        {
            DEBUG((ENT_MGT_ERRO, 
                "EnterpriseMgt : Size(%d) of device name in is more than MAX(%d) limit.\n", 
                sizeof(pDeviceList->DeviceName), MAX_DEVICE_NAME_SIZE));
            status = FALSE;
            return status;
        }
        
        Found = FALSE;

        if (CompareMem(pDeviceList->DeviceName, "NULL_DEV", sizeof("NULL_DEV")) == 0)
        {
            // DEBUG((ENT_MGT_INFO, 
            //     "EnterpriseMgt : Skipping NULL_DEV at %d for InterfaceNode 0x%p\n",
            //     j, pInterfacenode));
            pDeviceList = (HLOS_MNG_DEVICE*)((char*)pDeviceList + sizeof(HLOS_MNG_DEVICE));
            continue;
        }

        // Check if the device is already in the list.
        for (k = 0; k < pPolicy->NumberOfHlosDevices; k++)
        {
            if ( CompareMem(pDeviceList->DeviceName, 
                    pPolicy->HlosDeviceList[k].DeviceName, 
                    MAX_DEVICE_NAME_SIZE) == 0 )
            {
                Found = TRUE;
                break;
            }
        }

        if (!Found)
        {
            if (pPolicy->NumberOfHlosDevices >= MAX_HLOS_MANAGED_DEVICES)
            {
                DEBUG((ENT_MGT_ERRO, 
                    "EnterpriseMgt : Maximum devices reached for HLOS device names in store.\n"));
                status = FALSE;
                return status;
            }
            memscpy(pPolicy->HlosDeviceList[pPolicy->NumberOfHlosDevices].DeviceName, 
                MAX_DEVICE_NAME_SIZE,
                pDeviceList->DeviceName, 
                MAX_DEVICE_NAME_SIZE);

            pPolicy->NumberOfHlosDevices++;
        }

        pDeviceList = (HLOS_MNG_DEVICE*)((char*)pDeviceList + sizeof(HLOS_MNG_DEVICE));
    }

    return status;
}

/**
  Helper function to accumulate register, bitmask and value information from the given interface node.

  @param[in] pInterfacenode  Pointer to Interface node.
  @param[in, out] pPolicy     Buffer to store processed information.

  @retval TRUE  Successfully processed the request.
  @retval FALSE Failed to process this request.
**/
static BOOLEAN EnterpriseMgtUpdateRegXPolicyList (
    IN INTERFACE_NODE* pInterfacenode, 
    IN OUT ENT_MGT_PROCESSED_POLICY* pPolicy
    )
{
    BOOLEAN status = TRUE;
    BOOLEAN Found = FALSE;
    INTERFACE_ID_REGISTER *reg = NULL;
    UINT32 j = 0;
    UINT32 k = 0;
    
    reg = (INTERFACE_ID_REGISTER*)((char*)pInterfacenode + pInterfacenode->InterfaceIDOffset);

    for (j = 0; j < pInterfacenode->NumberOfInterfaceIDs; j++)
    {
        if (reg->BitPosition > MAX_ENT_MGT_BIT_POSITION )
        {
            DEBUG((ENT_MGT_ERRO, 
                "EnterpriseMgt : BitPosition %d is more than MAX(%d) value. Skipping it.\n", 
                reg->BitPosition, MAX_ENT_MGT_BIT_POSITION));
            reg = (INTERFACE_ID_REGISTER*)((char*)reg + sizeof(INTERFACE_ID_REGISTER));
            continue;
        }
		
        if (reg->RegisterAddress == 0)
        {
            // DEBUG((ENT_MGT_INFO, 
            //     "EnterpriseMgt : Skipping reg at %d for InterfaceNode 0x%p\n",
            //     j, pInterfacenode));
            reg = (INTERFACE_ID_REGISTER*)((char*)reg + sizeof(INTERFACE_ID_REGISTER));
            continue;
        }
        
        Found = FALSE;
        
        // Check if the register is already in the list. If found, update the current list.
        for (k = 0; k < pPolicy->NumMgtXRegs; k++)
        {
            if (pPolicy->MgtXRegList[k].RegisterAddress == reg->RegisterAddress)
            {
                Found = TRUE;
                pPolicy->MgtXRegList[k].BitMask |= (1 << reg->BitPosition);
                if (reg->BitValue)
                {
                    pPolicy->MgtXRegList[k].Value |= (1 << reg->BitPosition);
                }
                else
                {
                    pPolicy->MgtXRegList[k].Value &= ~(1 << reg->BitPosition);
                }
                break;
            }
        }

        if (!Found)
        {
            if (pPolicy->NumMgtXRegs >= MAX_ENT_MGT_REGISTERS)
            {
                DEBUG((ENT_MGT_ERRO, 
                    "EnterpriseMgt : Maximum number reached for MgtX registers in store.\n"));
                status = FALSE;
                return status;
            }

            pPolicy->MgtXRegList[pPolicy->NumMgtXRegs].RegisterAddress = reg->RegisterAddress;

            pPolicy->MgtXRegList[pPolicy->NumMgtXRegs].BitMask |= (1 << reg->BitPosition);
            if (reg->BitValue)
            {
                pPolicy->MgtXRegList[pPolicy->NumMgtXRegs].Value |= (1 << reg->BitPosition);
            }
            else
            {
                pPolicy->MgtXRegList[pPolicy->NumMgtXRegs].Value &= ~(1 << reg->BitPosition);
            }
            pPolicy->NumMgtXRegs++;
        }

        reg = (INTERFACE_ID_REGISTER*)((char*)reg + sizeof(INTERFACE_ID_REGISTER));
    }

    return status;
}

/**
  Helper function to read the feature node for the given feature type.

  @param[in] FeatureType  Feature Type to disable.
  @param[in] pCfg   Platform specific configuration read from xml converted .h file.

  @retval NULL : Unable to find the feature node.
  @retval FEATURE_NODE * : Valid feature node for the given feature type.
**/
static FEATURE_NODE* EntMgtGetFeatureNode (
    IN UINT32 FeatureType, 
    IN ENT_MGT_CONFIG* pCfg
    )
{
    FEATURE_NODE* pFeaturenode = NULL;
    FEATURE_NODE* pReturnFeaturenode = NULL;
    UINT32 i = 0;

    pFeaturenode = (FEATURE_NODE*)((char*)pCfg + pCfg->FeatureNodeOffset);

    for (i = 0; i < pCfg->NumberOfFeatures; i++)
    {
        if (FeatureType == pFeaturenode->FeatureType)
        {
            pReturnFeaturenode = pFeaturenode;
            break;
        }
        pFeaturenode = (FEATURE_NODE*)((char*)pFeaturenode + pFeaturenode->SizeofFeatureNode);
    }

    return pReturnFeaturenode;
}

/**
  Helper function to disable given Enterprise Management client policy hardware feature.

  @param[in] FeatureType  Feature Type to disable.
  @param[in] pEntMgtCfg   Platform specific configuration read from xml converted .h file.
  @param[in, out] pPolicy Buffer to store processed policy information.

  @retval TRUE  Successfully processed request to disable given feature type.
  @retval FALSE Failed to process this request.
**/
static BOOLEAN EnterpriseMgtProcessHWFeatureDisablePolicy (
    IN UINT32 FeatureType, 
    IN ENT_MGT_CONFIG* pEntMgtCfg, 
    IN OUT ENT_MGT_PROCESSED_POLICY* pPolicy
    )
{
    BOOLEAN status = TRUE;
    FEATURE_NODE* pFeaturenode = NULL;
    UINT32 i = 0;

    pFeaturenode = (FEATURE_NODE*)((char*)pEntMgtCfg + pEntMgtCfg->FeatureNodeOffset);

    pFeaturenode = EntMgtGetFeatureNode(FeatureType, pEntMgtCfg);
    if (pFeaturenode == NULL)
    {
        DEBUG((ENT_MGT_ERRO, 
            "EnterpriseMgt : FeatureType %d not available for this platform. Skipping.\n", FeatureType));
        status = TRUE;
        return status;
    }

    INTERFACE_NODE* pInterfacenode = (INTERFACE_NODE*)( (char*)pFeaturenode + 
                                                         pFeaturenode->InterfaceOffset );

    for (i = 0; i < pFeaturenode->NumInterfaces; i++)
    {
        status = EnterpriseMgtUpdateRegXPolicyList(pInterfacenode, pPolicy);
        if (status == FALSE)
        {
            DEBUG((ENT_MGT_ERRO, 
                "EnterpriseMgt : Failed to process Register Policy for Interface node "\
                "at position %d\n", i));
            return status;
        }

        status = EnterpriseMgtUpdateDeviceList(pInterfacenode, pPolicy, FALSE);
        if (status == FALSE)
        {
            DEBUG((ENT_MGT_ERRO, 
                "EnterpriseMgt : Failed to process device list for Interface node "\
                 "at position %d\n", i));
            return status;
        }

        pInterfacenode = (INTERFACE_NODE*)((char*)pInterfacenode + pInterfacenode->Size);
    }
    
    return status;
}

/**
  Enterprise Management helper function to map bit to feature type.

  @param[in] pStore      Structure for storing the bitmap and checksum values.
  @param[in] NumFeatures  Number of features to disable.
  @param[out] pFeatureList Array pointing to the features to disable.

  @retval EFI_SUCCESS            Successfully processed the request.
  @retval EFI_INVALID_PARAMETER  Invalid arguments.
  @retval EFI_CRC_ERROR          Checksum error.

**/

EFI_STATUS 
EnterpriseMgtMapBitsToFeatures(
    IN ENT_MGT_POLICY_STORE *pStore,
    IN UINT16 NumFeatures,
    OUT ENT_MGT_FEATURE_TYPE *pFeatureList
)
{
    EFI_STATUS status = EFI_SUCCESS;
    UINT16 i = 0;
    UINT16 j = 0;
    UINT32 index = 0;
    UINT32 Feature = 0;
    BOOLEAN allDone = FALSE;
    UINT32 FeatureBitMap = 0;
    UINT16 SavedCheckSum = 0;
    
    if ( NumFeatures == 0 ||
         pFeatureList == NULL ||
         pStore == NULL )
    {
        status = EFI_INVALID_PARAMETER;
        goto Exit;
    }

    SavedCheckSum = pStore->CheckSum; // Store the current checksum temporarily.
    pStore->CheckSum = 0;             // Set the checksum to zero for new computation.
    // Compute new checksum.
    pStore->CheckSum = CalculateCheckSum16((UINT16*)pStore, sizeof(ENT_MGT_POLICY_STORE));
    
    if (SavedCheckSum != pStore->CheckSum)
    {
        DEBUG((ENT_MGT_ERRO, "EnterpriseMgt : Checksum mismatch. Saved(0x%04x) != Computed(0x%04x).\n", 
            SavedCheckSum, pStore->CheckSum));
        status = EFI_CRC_ERROR;
        goto Exit;
    }
    
    for (i = 0; i < MAX_FEATURE_BITMAP_SIZE; i++)
    {
        FeatureBitMap = pStore->FeatureBitMap[i];

        if (FeatureBitMap)
        {
            for (j = 0; j < MAX_NUM_BITS_IN_ENT_MGT_REG; j++)
            {
                if (FeatureBitMap & (1 << j))
                {
                    Feature = i * MAX_NUM_BITS_IN_ENT_MGT_REG + j;
                    pFeatureList[index++] = (ENT_MGT_FEATURE_TYPE)Feature;
                    if (index == NumFeatures)
                    {
                        allDone = TRUE;
                        break;
                    }
                }
            }
        }

        if (allDone)
        {
            break;
        }
    }
    
Exit:
    return status;
}

/**
  Processes Enterprise Management client policies to disable hardware features
  and stores the processed information in policy structure.

  @param[in] pStore  Structure having list of features to disable.
  
  @retval EFI_SUCCESS            Successfully processed requested client policies.
  @retval EFI_NOT_FOUND          Platform configuration error.
  @retval EFI_OUT_OF_RESOURCES   Memory allocation failed for internal usage.
  @retval EFI_DEVICE_ERROR       Internal error while processing requested client policies.

**/
EFI_STATUS 
EFIAPI 
EnterpriseMgtProcessClientPolicies (
    IN ENT_MGT_POLICY_STORE *pStore
    )
{
    EFI_STATUS status = EFI_SUCCESS;
    UINT16 i = 0;
    ENT_MGT_CONFIG* pEntMgtCfg = NULL;
    ENT_MGT_PROCESSED_POLICY* pPolicy = NULL;
    UINT32 *pFeatureList = NULL;
    char VendorId[4] = {0};

    if (pStore->NumFeatures == 0)
    {
        DEBUG((ENT_MGT_ERRO, "EnterpriseMgt : No features to process.\n"));
        status = EFI_NOT_FOUND;
        goto Exit;
    }

    pEntMgtCfg = EnterpriseMgtGetPlatformCfg();
    if (pEntMgtCfg == NULL)
    {
        DEBUG((ENT_MGT_ERRO, "EnterpriseMgt : Unable to find platform configuration.\n"));
        status = EFI_NOT_FOUND;
        goto Exit;
    }
    
    VendorId[0] = (char)(pEntMgtCfg->VendorId);
    VendorId[1] = (char)(pEntMgtCfg->VendorId >>8);
    VendorId[2] = (char)(pEntMgtCfg->VendorId >>16);
    VendorId[3] = (char)(pEntMgtCfg->VendorId >>24);
    DEBUG((ENT_MGT_INFO, "EnterpriseMgt : Read configuration table with vendorId %a. \n", VendorId));
    pPolicy = (ENT_MGT_PROCESSED_POLICY*)AllocateZeroPool( sizeof(ENT_MGT_PROCESSED_POLICY) );
    if (pPolicy == NULL)
    {
        DEBUG((ENT_MGT_ERRO, "EnterpriseMgt : Memory allocation failed for pPolicy \n"));
        status = EFI_OUT_OF_RESOURCES;
        goto Exit;
    }
    
    pFeatureList = (UINT32 *)AllocateZeroPool( pStore->NumFeatures * sizeof(UINT32) );
    if (pFeatureList == NULL)
    {
        DEBUG((ENT_MGT_ERRO, "EnterpriseMgt : Memory allocation failed for pFeatureList \n"));
        status = EFI_OUT_OF_RESOURCES;
        goto Exit;
    }
    
    status = EnterpriseMgtMapBitsToFeatures(pStore, pStore->NumFeatures, pFeatureList);
    if (status != EFI_SUCCESS)
    {
        DEBUG((ENT_MGT_ERRO, "EnterpriseMgt : bit to feature mapping failed.\n"));
        goto Exit;
    }
        
    for (i = 0; i < pStore->NumFeatures; i++)
    {
        DEBUG((ENT_MGT_INFO, 
                "EnterpriseMgt : Processing disable policy for FeatureType[%d] : %d \n", 
                 i, pFeatureList[i]));

        if ( EnterpriseMgtIsSWFeature(pFeatureList[i]) ) 
        {
            if (EnterpriseMgtProcessSWFeatureDisablePolicy(pFeatureList[i]) != TRUE)
            {
                DEBUG((ENT_MGT_ERRO, 
                    "EnterpriseMgt : EnterpriseMgtProcessSWFeatureDisablePolicypFeatureList returned failure.\n"));
                status = EFI_DEVICE_ERROR;
                goto Exit;
            }
        }
        else
        {
            if (EnterpriseMgtProcessHWFeatureDisablePolicy(
                    pFeatureList[i], 
                    pEntMgtCfg, 
                    pPolicy) != TRUE)
            {
                DEBUG((ENT_MGT_ERRO, 
                    "EnterpriseMgt : EnterpriseMgtProcessHWFeatureDisablePolicy returned failure.\n"));
                status = EFI_DEVICE_ERROR;
                goto Exit;
            }
        }
    }
    
    if (pPolicy->NumMgtXRegs != 0)
    {
        status = EnterpriseMgtWriteToRegX(pPolicy) ? EFI_SUCCESS : EFI_DEVICE_ERROR;
        if (status != EFI_SUCCESS)
        {
            goto Exit;
        }
    }

    if (pPolicy->NumberOfHlosDevices != 0)
    {
        status = EnterpriseMgtRegisterForAcpiPlatform(pPolicy);
        if (status != EFI_SUCCESS)
        {
            goto Exit; 
        }
    }
    
Exit:
    if ((status != EFI_SUCCESS) && (pPolicy != NULL))
    {
        FreePool(pPolicy);
        pPolicy = NULL;
    }
    
    if (pFeatureList)
    {
        FreePool(pFeatureList);
        pFeatureList = NULL;
    }
    return status;
}
