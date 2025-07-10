/** @file Pwrup.c
#
#  Module Pwrup Application.
#
#  Copyright (c) 2020 - 2021 Qualcomm Technologies, Inc. All rights reserved.
#
#==============================================================================
#                              EDIT HISTORY
#
#
# when         who     what, where, why
# ----------   ---     ----------------------------------------------------------
# 06/16/2021   ay      Made changes to resolve misra issues
# 07/10/2020   yg      Use Chip family for cfg selection
# 04/07/2020   yg      Initial Revision
#==============================================================================
#**/

#include <Uefi.h>
#include <Library/BaseLib.h>
#include <Library/PrintLib.h>
#include <Library/UefiLib.h>
#include <Library/QcomLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/npa.h>
#include <Library/pmapp_npa.h>
#include <Protocol/EFITlmm.h>
#include <Protocol/EFIPmicTest.h>
#include <Protocol/EFIClock.h>
#include <Protocol/EFIChipInfo.h>
#include <Library/PcieTestUtils.h>

#include "Config.h"

#define PWR_ON        1
#define PWR_OFF       2
#define PWR_RST       3

extern PlatModulePwrupConfigType* PeripheralDevices[];

CHAR8 TempBuff[32];
volatile UINT32 stopfordebug = 0;
volatile UINT32 DbgPrintLevel = 0;

EFIChipInfoIdType CurrChipId;
EFIChipInfoVersionType CurrChipVer;
EFIChipInfoFamilyType CurrChipFamily;
UINT32 CurrPlatType;

EFI_STATUS PeripheralEnableOpn (EnGpioCfgType* EnGpio, UINTN PwrOn)
{
  UINT32 GpioEnVal;
  EFI_STATUS Status;

  while (EnGpio->GpioNum)
  {
     if (((EnGpio->EnableLevel & 1) ^ (PwrOn & 1)))
       GpioEnVal = GPIO_LOW_VALUE;
     else
       GpioEnVal = GPIO_HIGH_VALUE;

     if (DbgPrintLevel > 0) AsciiPrint ("Set GPIO %d to %d\r\n", EnGpio->GpioNum, GpioEnVal);

     Status = SetSocGpio (EnGpio->GpioNum, GpioEnVal);
     if (EFI_ERROR(Status))
     {
       DEBUG ((EFI_D_ERROR, "GPIO set failed\r\n"));
       return Status;
     }

     if (DbgPrintLevel > 0) DEBUG((EFI_D_ERROR, "Set GPIO succeeded\r\n"));

     ++EnGpio;
  }

  return EFI_SUCCESS;  
}

int PeripheralPowerOpn (RailsCfgType* RailsCfg, CHAR8* ClientName, UINTN PwrOperation)
{
   npa_client_handle TempHndl = NULL;
   char* OpStr = "";

   if (PwrOperation == PWR_ON) OpStr = "On";
   else if (PwrOperation == PWR_OFF) OpStr = "Off";

   if (DbgPrintLevel > 0) AsciiPrint ("Turning %a %a\r\n", ClientName, OpStr);

   while (RailsCfg && RailsCfg->NodeName)
   {
      npa_query_type  query = {0};

      /* Set to required voltage level and activate */
      if (RailsCfg->MicroVolts)
      {
         /* Get mV set handle */
         AsciiSPrint (TempBuff, sizeof(TempBuff), "%a/%a", RailsCfg->NodeName, "mV");
         TempHndl = npa_create_sync_client (TempBuff, ClientName, NPA_CLIENT_REQUIRED);
         if (TempHndl == NULL)
            return -2;
         if (npa_query_by_client (TempHndl, NPA_QUERY_CURRENT_STATE, &query) != NPA_QUERY_SUCCESS)
            return -3;
         RailsCfg->mvSetHandle = TempHndl;
      }

      /* Get enable handle */
      AsciiSPrint (TempBuff, sizeof(TempBuff), "%a/%a", RailsCfg->NodeName, "en");
      TempHndl = npa_create_sync_client (TempBuff, ClientName, NPA_CLIENT_REQUIRED);
      if (TempHndl == NULL)
         return -2;
      if (npa_query_by_client (TempHndl, NPA_QUERY_CURRENT_STATE, &query) != NPA_QUERY_SUCCESS)
         return -3;
      RailsCfg->EnHandle = TempHndl;

      /* Set Voltage if available */
      if (RailsCfg->MicroVolts)
         npa_issue_required_request (RailsCfg->mvSetHandle, RailsCfg->MicroVolts/1000);

      /* TODO: Turn off rails in reverse order */
      if (PwrOperation == PWR_ON)
      {
         npa_issue_required_request (RailsCfg->EnHandle, 1);
         if (DbgPrintLevel > 0) AsciiPrint ("Rail  %a  ON\r\n", RailsCfg->NodeName);
      }
      else if (PwrOperation == PWR_OFF)
      {
         npa_issue_required_request (RailsCfg->EnHandle, 0);
         if (DbgPrintLevel > 0) AsciiPrint ("Rail  %a  OFF\r\n", RailsCfg->NodeName);
      }

      // Do we need any delay between these rails turning ON?
      gBS->Stall (100);

      ++RailsCfg;
   }

   return 0;
}

EFI_STATUS PerformClockOpn (ClockCfgType* ClkCfg, UINTN PwrOperation)
{
   EFI_CLOCK_PROTOCOL *ClockProtocol = NULL;
   EFI_STATUS          Status = EFI_SUCCESS;

   if (ClkCfg == NULL)
      return EFI_INVALID_PARAMETER;

   Status = gBS->LocateProtocol(&gEfiClockProtocolGuid, NULL, (VOID **)&ClockProtocol);
   if (EFI_ERROR(Status)) 
   {
	   AsciiPrint ("Failed to locate CLOCK protocol\r\n");    
      return Status;
   }

   while (ClkCfg->ClockName != NULL)
   {
       Status = ClockProtocol->GetClockID (ClockProtocol, ClkCfg->ClockName, &ClkCfg->ClkId);
       if(EFI_SUCCESS != Status)
       {
           AsciiPrint ("ERROR: Failed to Get clock ID for %a\r\n", ClkCfg->ClockName);
          return Status;
       }

      if (PwrOperation == PWR_ON)
         Status = ClockProtocol->EnableClock(ClockProtocol, ClkCfg->ClkId);
      else if (PwrOperation == PWR_OFF)
         Status = ClockProtocol->EnableClock(ClockProtocol, ClkCfg->ClkId);

      if (EFI_ERROR(Status))
      {
         AsciiPrint ("Clock operation Failed\r\n");
         return EFI_DEVICE_ERROR;
      }

      ClkCfg++;
   }

   return EFI_SUCCESS;
}

EFI_STATUS InitResources (UINTN Argc, CHAR8** Argv)
{
  EFI_STATUS Status = EFI_SUCCESS;
  EFI_QCOM_PMIC_TEST_PROTOCOL *PmicTestProtocol = NULL;

  /* TODO: get a proper non test protocol from PMIC */
  Status = gBS->LocateProtocol(&gQcomPmicDriverTestProtocolGuid, NULL, (VOID **)&PmicTestProtocol);

  if (Status != EFI_SUCCESS)
  {
     AsciiPrint ("Pmic driver test protocol not found\n");
     return Status;
  }

  PmicTestProtocol->PmicPrmOsAuxDevInit();

  return EFI_SUCCESS;
}

EFI_STATUS GetCurrPlatCfg (PlatModulePwrupConfigType** RetPeriphCfgPtr)
{
   PlatModulePwrupConfigType* SelPeriphCfg = NULL, **PeriphCfgPtr = &PeripheralDevices[0];
   PlatModulePwrupConfigType* FmlyMatchPeriphCfg = NULL, *IdMatchPeriphCfg = NULL;

   if (RetPeriphCfgPtr == NULL)
      return EFI_INVALID_PARAMETER;

   if ((CurrChipId == 0) || (CurrChipFamily == 0))
      return EFI_INVALID_PARAMETER;

   PeriphCfgPtr = &PeripheralDevices[0];
   if (PeriphCfgPtr == NULL)
      return EFI_INVALID_PARAMETER;

  /* Loop through peripheral devices config and run test for peripheral on this particular platform */
  for ( ; *PeriphCfgPtr != NULL; ++PeriphCfgPtr)
  {
     if (((*PeriphCfgPtr)->ChipInfoId == 0) && ((*PeriphCfgPtr)->ChipFamilyId == 0))
        continue;

     //AsciiPrint ("Chip ID %X, Family %X\n", (*PeriphCfgPtr)->ChipInfoId, (*PeriphCfgPtr)->ChipFamilyId);

     if ((*PeriphCfgPtr)->ChipInfoId == 0)
     {
        if ((*PeriphCfgPtr)->ChipFamilyId == CurrChipFamily)
           FmlyMatchPeriphCfg = *PeriphCfgPtr;
     }
     else
     {
        if ((*PeriphCfgPtr)->ChipFamilyId != 0)
        {
           if (((*PeriphCfgPtr)->ChipFamilyId == CurrChipFamily) &&
               (CurrChipId == (*PeriphCfgPtr)->ChipInfoId))
           {
              SelPeriphCfg = *PeriphCfgPtr;
              break;
           }

        }
        else if (CurrChipId == (*PeriphCfgPtr)->ChipInfoId)
           IdMatchPeriphCfg = *PeriphCfgPtr;
     }
  }


  if (SelPeriphCfg == NULL)
  {
     if (IdMatchPeriphCfg != NULL)
        SelPeriphCfg = IdMatchPeriphCfg;
     else if (FmlyMatchPeriphCfg != NULL)
        SelPeriphCfg = FmlyMatchPeriphCfg;
     else
        return EFI_INVALID_PARAMETER;
  }

  *RetPeriphCfgPtr = SelPeriphCfg;

  return EFI_SUCCESS;
}

EFI_STATUS ProcessPowerup (UINTN Argc, CHAR8** Argv)
{
   PlatModulePwrupConfigType* PlatCfg = NULL;
   ModulePwrupConfigType* PeriphCfg = NULL, **PeriphCfgPtr = NULL;
   UINTN  PwrOpn = PWR_ON;
   char*  OpnStr = NULL;

   if ((GetCurrPlatCfg (&PlatCfg) != EFI_SUCCESS) || (PlatCfg == NULL))
   {
      AsciiPrint ("Peripheral module %a or the configuration for this chip not found\n", Argv[0]);
      return EFI_INVALID_PARAMETER;
   }

   PeriphCfgPtr = PlatCfg->PeriphModuleCfg;

   /* Loop through peripheral devices config and run test for peripheral on this particular platform */
   while ((*PeriphCfgPtr != NULL))
   {
     /* TODO: Add platform filter and version handling as well */
     if (AsciiStriCmp ((*PeriphCfgPtr)->PeriphName, Argv[0]) == 0)
     {
         PeriphCfg = *PeriphCfgPtr;
         break;
     }
     ++PeriphCfgPtr;
   }

   if (PeriphCfg == NULL)
   {
     AsciiPrint ("Peripheral module %a or the configuration for this chip not found\n", Argv[0]);
     return EFI_INVALID_PARAMETER;
   }

   if (Argc > 1)
   {
      //  Expected command would look like: Modpwr [on|off|rst]
      //  if no operation is given then ON is default

      if (AsciiStriCmp (Argv[1], "on") == 0)
         PwrOpn = PWR_ON;
      else if (AsciiStriCmp (Argv[1], "off") == 0)
         PwrOpn = PWR_OFF;
      else if (AsciiStriCmp (Argv[1], "rst") == 0)
         PwrOpn = PWR_RST;
   }
   else
      AsciiPrint ("Need one of on|off|rst operation specified, using \"on\" as default now\n");

   switch (PwrOpn)
   {
     case PWR_ON:
        OpnStr = "ON";
        if (PeriphCfg->ClkCfg)
          PerformClockOpn (PeriphCfg->ClkCfg, PwrOpn);

        if (PeripheralPowerOpn (PeriphCfg->RailsCfg, PeriphCfg->PeriphName, PwrOpn) < 0)
        {
           AsciiPrint ("Power operation failed\n");
           return EFI_DEVICE_ERROR;
        }

        if (PeripheralEnableOpn (PeriphCfg->EnGpio, 1) < 0)
        {
           AsciiPrint ("Enable operation failed\n");
           return EFI_DEVICE_ERROR;
        }
        break;

     case PWR_OFF:
        OpnStr = "OFF";
        if (PeripheralEnableOpn (PeriphCfg->EnGpio, 0) < 0)
        {
           AsciiPrint ("Enable operation failed\n");
           return EFI_DEVICE_ERROR;
        }

        if (PeripheralPowerOpn (PeriphCfg->RailsCfg, PeriphCfg->PeriphName, PwrOpn) < 0)
        {
           AsciiPrint ("Power operation failed\n");
           return EFI_DEVICE_ERROR;
        }

        if (PeriphCfg->ClkCfg)
          PerformClockOpn (PeriphCfg->ClkCfg, PwrOpn);
        break;

     case PWR_RST:
        OpnStr = "Reset";
        if (PeripheralEnableOpn (PeriphCfg->EnGpio, 0) < 0)
        {
           AsciiPrint ("Enable operation failed\n");
           return EFI_DEVICE_ERROR;
        }

        gBS->Stall (1000);

        if (PeripheralEnableOpn (PeriphCfg->EnGpio, 1) < 0)
        {
           AsciiPrint ("Enable operation failed\n");
           return EFI_DEVICE_ERROR;
        }
        break;

     default:
        break;
   }

   AsciiPrint ("Powered <%a> %a, on PCIe core %d\n", Argv[0], OpnStr, PeriphCfg->PCIeRCIndex);

   return EFI_SUCCESS;
}

/*
 *  Usage: PwrUp
 *    PwrUp tool can be used to powerup modules on QCom platforms from UEFI. It
 *    powers up a particular module either on/off based on arguments. If no argument
 *    is given, then it lists the available modules that can be given as argument.
 *
 *  Arguments:
 *    ModuleName <operation on/off>
 *
 *    ModuleName can be one of currently supported ones. ie wlan or wigig
 *    Operation can be one of on or off.
 *
 *  e.g. st fv3:\PwrUp "wlan on"
 */
EFI_STATUS
PwrupEntry (EFI_HANDLE         ImageHandle,
            EFI_SYSTEM_TABLE   *SystemTable)
{
  EFI_STATUS                  Status = EFI_SUCCESS;
  UINTN                       ErrorCode = 0;
  UINTN                       Argc = 0;
  CHAR8                     **Argv = NULL, **TempArgv = NULL;
  int i;

  Status = GetCmdLineArgs (ImageHandle, &Argc, &Argv);

  if (!EFI_ERROR(Status) && (Argc > 0))
  {
     TempArgv = Argv;

     /* Check if the app was launched by shell and the Cmd str is actually the
      * app name itself, ie it would be "app" or "app.efi", then again process
      * to split, this is because Ebl doesn't pass the name of app, but shell does &
      * other methods could yeild mixed results (like BDS launching apps via Menu, etc) */
     if ((AsciiStriCmp (Argv[0], "pwrup") == 0) ||
         (AsciiStriCmp (Argv[0], "pwrup.efi") == 0))
     {
       --Argc;
       if (Argc == 0)
       {
         FreePool (Argv);
         TempArgv = NULL;
         Argv = NULL;

         /* Here, either return back or assume default values as required
          * if an argument is expected. If this image doesn't need any argument
          * then this whole block of code can be removed */
         AsciiPrint ("No Command to process, or assuming default values... \r\n");
   //      return EFI_SUCCESS;
       }
       else
         ++Argv;
     }
  }

  for (i=0; i<Argc; ++i)
  {
     if (AsciiStriCmp (Argv[i], "dbg") == 0)
        ++stopfordebug;

     if (AsciiStriCmp (Argv[i], "lvl") == 0)
     {
        if ((i+1) < Argc)
           DbgPrintLevel = AsciiStrHexToUintn (Argv[++i]);
     }

 //    AsciiPrint (" %d : %a\r\n", i, Argv[i]);
  }

  if (GetTargetPlatformInfo (&CurrChipId, &CurrChipVer, &CurrChipFamily, &CurrPlatType) != 0)
     return EFI_DEVICE_ERROR;

  //AsciiPrint ("Chip ID %X, Ver %d, Family %X, Type %X\n", CurrChipId, CurrChipVer, CurrChipFamily, CurrPlatType);

  if (InitResources (Argc, Argv) != EFI_SUCCESS)
  {
     AsciiPrint ("Module initialization failed\n");
     return EFI_DEVICE_ERROR;
  }

  if (Argc)
     ErrorCode = ProcessPowerup (Argc, Argv);
  else
  {
     PlatModulePwrupConfigType* PlatCfg = NULL;

     AsciiPrint ("Specify the module name to powerup, supported modules list:\n");

     if ((GetCurrPlatCfg (&PlatCfg) != EFI_SUCCESS) || (PlatCfg == NULL))
     {
        AsciiPrint ("Config for current target/platform not found..!!\n");
     }
     else
     {
        ModulePwrupConfigType** PeriphCfg = NULL;

        PeriphCfg = PlatCfg->PeriphModuleCfg;
        /* Loop through peripheral devices config and run test for peripheral on this particular platform */
        while (*PeriphCfg)
        {
           AsciiPrint (" %a\n", (*PeriphCfg)->PeriphName);
           ++PeriphCfg;
        }
     }

  }

  if (TempArgv)
    FreePool (TempArgv);

  if (ErrorCode != 0)
    AsciiPrint ("Error Code: %d\r\n", ErrorCode);

  return Status;
}

