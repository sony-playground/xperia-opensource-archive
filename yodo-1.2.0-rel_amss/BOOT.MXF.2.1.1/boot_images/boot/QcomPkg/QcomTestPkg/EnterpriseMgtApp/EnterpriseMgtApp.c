/** @file EnterpriseMgtApp.c
   
  Application to test Enterprise Management lib and driver functionality.
  
  Copyright 2020 Qualcomm Technologies, Inc.  All Rights Reserved.
  Qualcomm Technologies Proprietary and Confidential.
   
**/

/*=============================================================================
 $Header: //components/rel/core.boot/6.1.1/QcomPkg/QcomTestPkg/EnterpriseMgtApp/EnterpriseMgtApp.c#1 $
                              EDIT HISTORY


  when         who     what, where, why
  ----------   ---     -------------------------------------------------------
 02/21/2020     hh    Initial version.
=============================================================================*/

#include <Uefi.h>
#include <stdlib.h>
#include <Library/UefiLib.h>
#include <Library/QcomLib.h>
#include <Library/QcomUtilsLib.h>
#include <Library/BaseLib.h>
#include <Library/DebugLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/BaseMemoryLib.h>
#include <Protocol/LoadedImage.h>
#include <Protocol/EfiWinAcpiUpdate.h>
#include <Protocol/AcpiSystemDescriptionTable.h>
#include <Library/UefiRuntimeServicesTableLib.h>
#include <Protocol/VariablePolicy.h>
#include <Protocol/EFIEnterpriseMgt.h>
#include <EnterpriseMgtLib.h>
#define ENTP_MGMT_TEST_GPIO
#ifdef ENTP_MGMT_TEST_GPIO
#include <Protocol/EFITlmm.h>
#endif

/**
  Helper function to try tampering UEFI NV variable.
  
  @retval EFI_STATUS  Status of return code.
**/
EFI_STATUS EnterpriseMgtTamperVar(VOID)
{
    EFI_STATUS status = EFI_DEVICE_ERROR;
    EFI_GUID EnterpriseMgtClientPoliciesGuid = ENT_MGT_CLIENT_POLICIES_GUID;
    
    AsciiPrint("EnterpriseMgtApp : Try deleting UEFI NV variable : %s\n", 
        ENT_MGT_CLIENT_POLICIES_NAME);
        
    status = gRT->SetVariable(
                    ENT_MGT_CLIENT_POLICIES_NAME, 
                    &EnterpriseMgtClientPoliciesGuid, 
                    ENT_MGT_CLIENT_POLICIES_ATTR, 
                    0,
                    NULL
                    );
                    
    AsciiPrint( "EnterpriseMgtApp : Attempted deleting UEFI variable %s and received status = 0x%p \n", 
        ENT_MGT_CLIENT_POLICIES_NAME, status);
        
    if ( status == EFI_WRITE_PROTECTED)
    {
        AsciiPrint("EnterpriseMgtApp : UEFI variable is LOCKED..!!\n");
    }
    else if ( status == EFI_NOT_FOUND)
    {
        AsciiPrint("EnterpriseMgtApp : UEFI variable not found..!!\n");
    }
    else
    {
        AsciiPrint("EnterpriseMgtApp : UEFI variable was not LOCKED. Deleted now..!!\n");
    }
    
    return status;
}

/**
  Helper function to Dump UEFI NV variable.
  
  @retval EFI_STATUS  Status of return code.
**/
EFI_STATUS EnterpriseMgtDumpUefiNvVar(VOID)
{
    ENT_MGT_POLICY_STORE *pStore = NULL;
    EFI_STATUS  status = EFI_DEVICE_ERROR;
    EFI_GUID EnterpriseMgtClientPoliciesGuid = ENT_MGT_CLIENT_POLICIES_GUID;
    UINT32 Attributes = ENT_MGT_CLIENT_POLICIES_ATTR;
    UINTN PolicySize = 0;
    UINT32 i = 0;
        
    PolicySize = sizeof(ENT_MGT_POLICY_STORE);
    pStore = (ENT_MGT_POLICY_STORE *)AllocateZeroPool(PolicySize);
    if (pStore == NULL)
    {
        status = EFI_OUT_OF_RESOURCES;
        AsciiPrint("EnterpriseMgtApp : Memory allocation failed for policy store..!!\n");
        goto Exit;
    }
    
    status = gRT->GetVariable(
              ENT_MGT_CLIENT_POLICIES_NAME,
              &EnterpriseMgtClientPoliciesGuid,
              &Attributes,
              &PolicySize,
              pStore);
              
    if ( status == EFI_NOT_FOUND)
    {
        AsciiPrint("EnterpriseMgtApp : UEFI variable %s not found.\n", ENT_MGT_CLIENT_POLICIES_NAME);
        goto Exit;
    }
    else
    {
        AsciiPrint("= %s(%d) =\n", ENT_MGT_CLIENT_POLICIES_NAME, PolicySize);
        AsciiPrint("HeadCookie            : 0x%04x\n", pStore->HeadCookie);
        AsciiPrint("PolicyVersion         : 0x%04x\n", pStore->PolicyVersion);
        AsciiPrint("NumFeatures           : 0x%04x\n", pStore->NumFeatures);
        AsciiPrint("CheckSum              : 0x%04x\n", pStore->CheckSum);
        AsciiPrint("********* FeatureBitMap ************\n");
        for (i = 0; i < MAX_FEATURE_BITMAP_SIZE; i++)
        {
            AsciiPrint("[%02d]FeatureBitMap   : 0x%08x\n", i, pStore->FeatureBitMap[i]);
        }
        AsciiPrint("TailCookie            : 0x%04x\n", pStore->TailCookie);
        AsciiPrint("Reserved              : 0x%04x\n", pStore->Reserved);
        AsciiPrint("=================================\n");
    }
    
Exit:  
    if (pStore)
    {
        FreePool(pStore);
        pStore = NULL;
    }
    
    return status;
}

/**
  Helper function to lock the EnterpriseMgt UEFI NV variable.
  
  @retval EFI_STATUS  Status of return code.
**/
static EFI_STATUS EnterpriseMgtLockNowVar(VOID)
{
    EFI_STATUS status = EFI_DEVICE_ERROR;
    EFI_QCOM_ENTERPRISEMGT_PROTOCOL *pEntpProt = NULL;

    status = gBS->LocateProtocol(&gQcomEnterpriseMgtProtocolGuid, NULL, (VOID **)&pEntpProt);
    if (EFI_ERROR(status))
    {
        AsciiPrint("EnterpriseMgtApp : Locate EnterpriseMgt Protocol failed, status = 0x%p\n", status);
        goto Exit;
    }

    status = pEntpProt->EnterpriseMgtLockNowVar();
    if (EFI_ERROR (status))
    {
        AsciiPrint("EnterpriseMgtApp : EnterpriseMgtLockNowVar failed with Status = 0x%p\n", status);
        goto Exit;
    }
    else
    {
        AsciiPrint("EnterpriseMgtApp : Locked UEFI variable %s successfully.\n", 
            ENT_MGT_CLIENT_POLICIES_NAME);
    }

Exit: 
    return status;
}

/**
  Helper function to print usage of this test app.
**/
static VOID PrintHelp (VOID)
{
    AsciiPrint("Supported options: \n");
    AsciiPrint("EnterpriseMgtApp.efi -Help               : To print supported options.\n");
    AsciiPrint("EnterpriseMgtApp.efi -FeatureType <feature numbers> : To disable given feature(s).\n");
    AsciiPrint("EnterpriseMgtApp.efi -DeletePolicy       : To delete the stored policy from NV.\n");
    AsciiPrint("EnterpriseMgtApp.efi -LockNowVar         : To lock UEFI NV variable.\n");
    AsciiPrint("EnterpriseMgtApp.efi -TamperVar          : To try deleting UEFI NV variable.\n");
    AsciiPrint("EnterpriseMgtApp.efi -DumpStore          : To print current EnterpriseMgt UEFI variable.\n");
#ifdef ENTP_MGMT_TEST_GPIO
    AsciiPrint("EnterpriseMgtApp.efi -SetGpio <GpioNum> <HIGH/LOW> : To configure GPIO output to HIGH/LOW.\n");
    AsciiPrint("EnterpriseMgtApp.efi -GetGpio <GpioNum>  : To read GPIO output status\n");
#endif
    AsciiPrint("EnterpriseMgtApp.efi -Reboot             : To reboot the device gracefully\n");
}

static int hexval(char c)
{
    if (c >= '0' && c <= '9')
        return c - '0';
    else if (c >= 'a' && c <= 'f')
        return c - 'a' + 10;
    else if (c >= 'A' && c <= 'F')
        return c - 'A' + 10;

    return 0;
}

static int isdigit(int c)
{
    return ((c >= '0') && (c <= '9'));
}

static int isxdigit(int c)
{
    return isdigit(c) || ((c >= 'a') && (c <= 'f')) || ((c >= 'A') && (c <= 'F'));
}

static long StringToInt(const char *num)
{
    long value = 0;
    int neg = 0;

    if (num[0] == '0' && num[1] == 'x') {
        // hex
        num += 2;
        while (*num && isxdigit(*num))
            value = value * 16 + hexval(*num++);
    } else {
        // decimal
        if (num[0] == '-') {
            neg = 1;
            num++;
        }
        while (*num && isdigit(*num))
            value = value * 10 + *num++  - '0';
    }

    if (neg)
        value = -value;

    return value;
}

/**
  Entry point for EnterpriseMgtAppMain APP

  @param[in] ImageHandle    The firmware allocated handle for the EFI image.  
  @param[in] SystemTable    A pointer to the EFI System Table.
  
  @retval EFI_SUCCESS           Executed successfully.
  @retval EFI_WRITE_PROTECTED   UEFI NV variable is write protected.
**/
EFI_STATUS
EFIAPI
EnterpriseMgtAppMain ( 
                IN EFI_HANDLE         ImageHandle,
                IN EFI_SYSTEM_TABLE   *SystemTable
                )
{
    EFI_STATUS status = EFI_SUCCESS;
    UINTN Argc = 0;
    CHAR8 **Argv = NULL;
    UINTN i = 0;
    UINTN j = 0;
    ENT_MGT_FEATURE_TYPE *pFeatureList = NULL;
    UINT16 NumFeatures = 0; 
    BOOLEAN CalllibAPI = FALSE;
    BOOLEAN LockNowVar = FALSE;
    BOOLEAN TamperVar = FALSE;
    BOOLEAN DumpStore = FALSE;
#ifdef ENTP_MGMT_TEST_GPIO
    BOOLEAN SetGpio = FALSE;
    BOOLEAN GetGpio = FALSE;
    UINT16 GpioNum = 0;
    TLMM_ValueType GpioValue = GPIO_LOW_VALUE;
    EFI_TLMM_PROTOCOL *pTLMMProtocol = NULL;
#endif
    status = GetCmdLineArgs (
                ImageHandle,
                &Argc,
                &Argv
                );

    if (EFI_ERROR(status))
    {
        AsciiPrint ("EnterpriseMgtApp : Failed to get cmd line args with status 0x%x\n", status);
        return status;  
    }

    for (i = 0; i < Argc; ++i)
    {
        if ((AsciiStriCmp (Argv[i], "EnterpriseMgtApp") == 0) ||
            (AsciiStriCmp (Argv[i], "EnterpriseMgtApp.efi") == 0))
        {
          continue;
        }
        
        if (AsciiStriCmp (Argv[i], "-Help") == 0)
        {
            break;
        }
        else if (AsciiStriCmp (Argv[i], "-FeatureType") == 0)
        {
            pFeatureList = (ENT_MGT_FEATURE_TYPE *)AllocateZeroPool(sizeof(ENT_MGT_FEATURE_TYPE) * Argc);
            if (pFeatureList == NULL)
            {
                AsciiPrint("EnterpriseMgtApp : Failed to allocate memory for pFeatureList\n");
                break;
            }
            CalllibAPI = TRUE;
            NumFeatures = 0;
            for(j = i+1; j < Argc; j++)
            {
                pFeatureList[NumFeatures] = StringToInt(Argv[j]);
                AsciiPrint("EnterpriseMgtApp : Disable FeatureType : %d\n", pFeatureList[NumFeatures]);
                NumFeatures++;
            }
            break;
        }
        else if (AsciiStriCmp (Argv[i], "-DeletePolicy") == 0)
        {
            NumFeatures = 0;
            pFeatureList = NULL;
            CalllibAPI = TRUE;
            break;
        }
        else if (AsciiStriCmp (Argv[i], "-LockNowVar") == 0)
        {
            LockNowVar = TRUE;
            break;
        }
        else if (AsciiStriCmp (Argv[i], "-TamperVar") == 0)
        {
            TamperVar = TRUE;
            break;
        }
        else if (AsciiStriCmp (Argv[i], "-DumpStore") == 0)
        {
            DumpStore = TRUE;
            break;
        }
#ifdef ENTP_MGMT_TEST_GPIO
        else if (AsciiStriCmp (Argv[i], "-SetGpio") == 0)
        {
            if (i + 2 < Argc)
            {
                SetGpio = TRUE;
                GpioNum = StringToInt(Argv[i+1]);
                if (AsciiStriCmp (Argv[i+2], "HIGH") == 0)
                {
                    GpioValue = GPIO_HIGH_VALUE;
                }
                else if (AsciiStriCmp (Argv[i+2], "LOW") == 0)
                {
                    GpioValue = GPIO_LOW_VALUE;
                }
                else
                {
                    SetGpio = FALSE;
                    AsciiPrint("EnterpriseMgtApp : Invalid argument %s\n", Argv[i+2]);
                    PrintHelp();
                }
            }
            else
            {
                AsciiPrint("EnterpriseMgtApp : Invalid number of arguments.\n");
                PrintHelp();
            }
            break;
        }
        else if (AsciiStriCmp (Argv[i], "-GetGpio") == 0)
        {
            if (i + 1 < Argc)
            {
                GetGpio = TRUE;
                GpioNum = StringToInt(Argv[i+1]);
            }
            else
            {
                AsciiPrint("EnterpriseMgtApp : Invalid number of arguments.\n");
                PrintHelp();
            }
            break;
        }
#endif
        else if (AsciiStriCmp (Argv[i], "-Reboot") == 0)
        {
            status = FlushVariableServices();
            if (status != EFI_SUCCESS)
            {
                AsciiPrint("EnterpriseMgtApp : Unable to flush variables to NV memory. Status = 0x%p\n", status);
            }
            AsciiPrint("EnterpriseMgtApp : Rebooting the device..\n");
            gST->RuntimeServices->ResetSystem (EfiResetCold, EFI_SUCCESS, 0, NULL);
        }
        else
        {
            AsciiPrint("EnterpriseMgtApp : Invalid argument %s\n", Argv[i]);
            break;
        }
    }
    
    if (CalllibAPI)
    {
        // Use API to store client policy to UEFI NV variable or 
        // Use API to delete UEFI NV variable.
        status = EnterpriseMgtSetFeaturesToDisable(NumFeatures, pFeatureList);
        if (status == EFI_WRITE_PROTECTED)
        {
            AsciiPrint("EnterpriseMgtApp : Variable %s is LOCKED..!! Status = 0x%p\n", 
                ENT_MGT_CLIENT_POLICIES_NAME, status);
        }
        else if ((status != EFI_SUCCESS))
        {
            AsciiPrint("EnterpriseMgtApp : EnterpriseMgtSetFeaturesToDisable failed. Status = 0x%p\n",
                status);
        }
        else
        {
            AsciiPrint("EnterpriseMgtApp : EnterpriseMgtSetFeaturesToDisable processed successfully\n");
        }
        goto done;
    }
    else if (LockNowVar)
    {
        status = EnterpriseMgtLockNowVar();
        if ((status != EFI_SUCCESS))
        {
            AsciiPrint("EnterpriseMgtApp : EnterpriseMgtLockNowVar failed. Status = 0x%p\n", status);
        }
        goto done;
    }    
    else if (TamperVar)
    {
        // Validate UEFI NV locking status.
        status = EnterpriseMgtTamperVar();
        if ((status != EFI_SUCCESS))
        {
            AsciiPrint("EnterpriseMgtApp : EnterpriseMgtTamperVar failed. Status = 0x%p\n", 
                status);
        }
        goto done;
    }
    else if (DumpStore)
    {
        // Dump UEFI NV variable.
        status = EnterpriseMgtDumpUefiNvVar();
        if ((status != EFI_SUCCESS))
        {
            AsciiPrint("EnterpriseMgtApp : EnterpriseMgtDumpUefiNvVar failed. Status = 0x%p\n", 
                status);
        }
        goto done;
    }
#ifdef ENTP_MGMT_TEST_GPIO
    else if ((GetGpio == TRUE) || (SetGpio == TRUE))
    {
        status = gBS->LocateProtocol( &gEfiTLMMProtocolGuid, NULL, (void**)&pTLMMProtocol);
        if ((status != EFI_SUCCESS) || pTLMMProtocol == NULL )
        {
            AsciiPrint("EnterpriseMgtApp : Failed to locate TLMM Protocol. Status = 0x%p\n", status);
            goto done;
        }
        
        if (SetGpio)
        {
            /*
              GpioOut() and GpioIn() API's will use only GpioNum from the EFI_GPIO_CFG macro. Rest 
              arguments are not used. Only ConfigGpio() API consumes them for configuring GPIO's 
              ConfigGpio() will be programming TLMM_GPIO_CFG* registers.
              GpioOut() will be writing to TLMM_GPIO_IN_OUT* registers.
              GpioIn() will be reading TLMM_GPIO_IN_OUT* registers.
              TLMM read/write logic is implemented in TLMMHWLib/HALgpioCore.c.
            */
            status = pTLMMProtocol->GpioOut( 
                            (UINT32)EFI_GPIO_CFG(GpioNum, 0, GPIO_OUTPUT, GPIO_NO_PULL, GPIO_2MA), 
                             GpioValue );
                             
            if ((status != EFI_SUCCESS))
            {
                AsciiPrint("EnterpriseMgtApp : GpioOut() failed. Status = 0x%p\n", status);
                goto done;
            }
            AsciiPrint("EnterpriseMgtApp : Set the GPIO pin %d to value %a\n", 
                GpioNum, GpioValue ? "GPIO_HIGH_VALUE" : "GPIO_LOW_VALUE");
        }
        
        if (GetGpio)
        {
            status = pTLMMProtocol->GpioIn( 
                            (UINT32)EFI_GPIO_CFG(GpioNum, 0, GPIO_OUTPUT, GPIO_NO_PULL, GPIO_2MA), 
                             &GpioValue);
                             
            if ((status != EFI_SUCCESS))
            {
                AsciiPrint("EnterpriseMgtApp : GpioIn() failed. Status = 0x%p\n", status);
                goto done;
            }
            AsciiPrint("EnterpriseMgtApp : Read the GPIO pin %d as value %a\n", 
                GpioNum, GpioValue ? "GPIO_HIGH_VALUE" : "GPIO_LOW_VALUE");
        }
        goto done;
    }
#endif
    else
    {
        PrintHelp();
    }
    
done:
    if (pFeatureList)
    {
        FreePool(pFeatureList);
        pFeatureList = NULL;
    }
    
    if (Argv)
    {
        FreePool (Argv);
        Argv = NULL;
    }
    
    return status;
}
