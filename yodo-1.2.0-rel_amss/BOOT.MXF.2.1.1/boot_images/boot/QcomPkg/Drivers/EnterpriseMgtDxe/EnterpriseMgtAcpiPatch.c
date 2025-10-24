/**
  @file EnterpriseMgtAcpiPatch.c
  @brief EnterpriseMgt dxe functions to register a callback for ACPI platform 
  dxe init event.
*/
/*=============================================================================
  Copyright (c) 2020 Qualcomm Technologies, Incorporated.
  All rights reserved.
  Qualcomm Technologies Inc., Confidential and Proprietary.
=============================================================================*/
/*=============================================================================
 $Header: //components/rel/core.boot/6.1.1/QcomPkg/Drivers/EnterpriseMgtDxe/EnterpriseMgtAcpiPatch.c#1 $
                              EDIT HISTORY


 when          who     what, where, why
 ----------    ---    --------------------------------------------------------
 02/21/2020     hh    Initial version.
=============================================================================*/
#include <Uefi.h>
#include <Library/UefiLib.h>
#include <Library/UefiCfgLib.h>
#include <Library/DebugLib.h>
#include <Protocol/EFIAcpiPlatform.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <string.h>
#include <Protocol/EFIEnterpriseMgt.h>
#include "EnterpriseMgtDxeBaseDef.h"
#include "EnterpriseMgtAcpiPatch.h"

/**
  Callback function for ACPI platform dxe init event.

  @param[in]  Event     Event whose notification function is being invoked
  @param[in]  Context   Pointer to the notification function's context
**/
VOID EFIAPI EnterpriseMgtOnAcpiPlatformInitCallback (
    IN EFI_EVENT  Event,
    IN VOID      *Context
    )
{
    EFI_STATUS status = EFI_SUCCESS;
    ENT_MGT_PROCESSED_POLICY *pPolicy = Context;
    EFI_QCOM_ACPIPLATFORM_PROTOCOL *pAcpiPlatProto = NULL;
    CHAR8 **ppDeviceNameList = NULL;
    UINT8 *pSTAStatusList = NULL;
    UINT32 *pDeviceNameLengthList = NULL;
    UINT32 i = 0;
            
    DEBUG((ENT_MGT_INFO, "EnterpriseMgt : Received AcpiPlatform Init callback.\n"));
    
    if (pPolicy == NULL)
    {
        status = EFI_COMPROMISED_DATA;
        DEBUG ((ENT_MGT_ERRO, "EnterpriseMgt : Context is NULL!!\n"));
        goto Exit;
    }
    
    if ( (pPolicy->NumberOfHlosDevices > 0) && 
        (pPolicy->NumberOfHlosDevices <= MAX_HLOS_MANAGED_DEVICES) )
    {
        ppDeviceNameList = (CHAR8 **)AllocateZeroPool(sizeof(CHAR8 *) * pPolicy->NumberOfHlosDevices);
        if (ppDeviceNameList == NULL)
        {
            DEBUG((ENT_MGT_ERRO, "EnterpriseMgt : AllocateZeroPool failed for ppDeviceNameList.\n"));
            goto Exit;
        }
    
        pDeviceNameLengthList = (UINT32 *)AllocateZeroPool(sizeof(UINT32) * pPolicy->NumberOfHlosDevices);
        if (pDeviceNameLengthList == NULL)
        {
            DEBUG((ENT_MGT_ERRO, 
                "EnterpriseMgt : AllocateZeroPool failed for pDeviceNameLengthList.\n"));
            goto Exit;
        }
        
        pSTAStatusList = (UINT8 *)AllocateZeroPool(sizeof(CHAR8) * pPolicy->NumberOfHlosDevices);
        if (pSTAStatusList == NULL)
        {
            DEBUG((ENT_MGT_ERRO, "EnterpriseMgt : AllocateZeroPool failed for pSTAStatusList.\n"));
            goto Exit;
        }
       
        for (i = 0; i < pPolicy->NumberOfHlosDevices; i++)
        {
            ppDeviceNameList[i] = (CHAR8 *)AllocateZeroPool(MAX_DEVICE_NAME_SIZE);
            if (ppDeviceNameList[i] == NULL)
            {
                DEBUG((ENT_MGT_ERRO, 
                    "EnterpriseMgt : AllocateZeroPool failed for ppDeviceNameList[%d]\n", i));
                goto Exit;
            }
            
            memscpy(ppDeviceNameList[i], MAX_DEVICE_NAME_SIZE, pPolicy->HlosDeviceList[i].DeviceName, MAX_DEVICE_NAME_SIZE);
            pDeviceNameLengthList[i] = sizeof(pPolicy->HlosDeviceList[i].DeviceName);
            pSTAStatusList[i] = 0; // Disable device status

            DEBUG((ENT_MGT_INFO, "EnterpriseMgt : Registering Device %a for STAStatus 0x%x\n", 
                ppDeviceNameList[i], pSTAStatusList[i]));
        }

        // Locate the AcpiPlatform protocol
        status = gBS->LocateProtocol(&gQcomAcpiPlatformProtocolGuid,  NULL, (VOID**) &pAcpiPlatProto);
        if (EFI_ERROR(status))
        {
            DEBUG((ENT_MGT_ERRO, 
                "EnterpriseMgt : Locate ACPI Protocol failed, status = 0x%p\n", status));
            goto Exit;
        }
        
        status = pAcpiPlatProto->AmlRegisterDevicesForDsdtStaPatch( pAcpiPlatProto,
                                                           ppDeviceNameList,
                                                           pDeviceNameLengthList,
                                                           pSTAStatusList,
                                                           pPolicy->NumberOfHlosDevices);
        if (EFI_ERROR(status))
        {
            DEBUG((ENT_MGT_ERRO, 
               "EnterpriseMgt : register AmlRegisterDevicesForDsdtStaPatch failed with Status = (0x%p)\n",
               status));
            goto Exit;
        }
    }
    
Exit:
    // ASSERT_EFI_ERROR(status);

    if ((pPolicy != NULL) && (ppDeviceNameList != NULL))
    {
        for (i = 0; i < pPolicy->NumberOfHlosDevices; i++)
        {
            if (ppDeviceNameList[i])
            {
                FreePool(ppDeviceNameList[i]);
                ppDeviceNameList[i] = NULL;
            }
        }
    }
    
    if (ppDeviceNameList)
    {
        FreePool(ppDeviceNameList);
        ppDeviceNameList = NULL;
    }
    
    if (pDeviceNameLengthList)
    {
        FreePool(pDeviceNameLengthList);
        pDeviceNameLengthList = NULL;
    }
    
    if (pSTAStatusList)
    {
        FreePool(pSTAStatusList);
        pSTAStatusList = NULL;
    }
}

/**
  Function to register a callback for ACPI platform dxe init event.

  @retval EFI_SUCCESS           Registered successfully.
  @retval CreateEvent() or  RegisterProtocolNotify() returned value.
**/
EFI_STATUS EnterpriseMgtRegisterForAcpiPlatform (
    IN ENT_MGT_PROCESSED_POLICY* pPolicy
    )
{
    EFI_STATUS  status = EFI_DEVICE_ERROR;
    EFI_EVENT AcpiPlatformInitEvent = NULL;
    VOID *AcpiPlatInitToken = NULL;
    
    DEBUG((ENT_MGT_INFO, 
        "EnterpriseMgt : Registering for AcpiPlatform Init callback.\n"));
    
    // Register ACPI table event
    status = gBS->CreateEvent( EVT_NOTIFY_SIGNAL,
                               TPL_CALLBACK,
                               EnterpriseMgtOnAcpiPlatformInitCallback,
                               pPolicy,
                               &AcpiPlatformInitEvent );
    if ( EFI_ERROR(status))
    {
        DEBUG((ENT_MGT_ERRO, 
            "EnterpriseMgt : CreateEvent failed for ACPI table. Status = (0x%p)\n", status));
        goto Exit;
    }

    status = gBS->RegisterProtocolNotify(&gQcomAcpiPlatformProtocolGuid,
                                         AcpiPlatformInitEvent,
                                         (VOID *)&AcpiPlatInitToken );
    if ( EFI_ERROR(status))
    {
        DEBUG((ENT_MGT_ERRO, 
            "EnterpriseMgt : RegisterProtocolNotify failed for gQcomAcpiPlatformProtocolGuid. \
            Status = (0x%p)\n", status));
        goto Exit;
    }
    
Exit:
    // ASSERT_EFI_ERROR(status);
    return status;
}