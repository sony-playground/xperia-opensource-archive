/** 
 @file PcieLowBattCharging.c

  Implements functionalities to manage Pcie core power during low battery 
  charging use case.

  Copyright (c) 2018-2022 Qualcomm Technologies, Inc.
  All Rights Reserved.
  Confidential and Proprietary - Qualcomm Technologies, Inc.

**/


/*=============================================================================
                              EDIT HISTORY


 when       who     what, where, why
 --------   ----    ----------------------------------------------------------
 12/18/20   yg      Migrated to new interface
 01/31/19   ts      Executing LPM only when Display receives the hint
 10/30/18   ts      Initial version
=============================================================================*/


#include <Uefi.h>
#include <Uefi/UefiSpec.h>
#include <Library/UefiLib.h>
#include <Library/UefiApplicationEntryPoint.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiRuntimeServicesTableLib.h>
#include <Library/DebugLib.h>
#include <Pi/PiStatusCode.h>
#include <Protocol/StatusCode.h>
#include <Protocol/ReportStatusCodeHandler.h>
#include <Library/BaseMemoryLib.h>
#include <Lpm.h>
#include "PcieConfig_i.h"
#include <Protocol/EFIChargerEx.h>

EFI_STATUS ConfigLibDeinitializeAllPcieCores (VOID);

#define REGISTER_CHG_CB       1
#define UNREGISTER_CHG_CB     0


/*******************************************************************************
 *
 *            Private functions
 *
 ******************************************************************************/
STATIC
EFI_STATUS
PcieConfigLibLPMEnter (void)
{
   STATIC BOOLEAN InLpm = FALSE;
   EFI_STATUS     Status = EFI_SUCCESS;
 
   /* This function cannot be executed more than once
    * as there is no way to exit LPM in UEFI for PCIe TODO: Check if true */
   if (InLpm == TRUE)
      return EFI_SUCCESS;
 
   Status = ConfigLibDeinitializeAllPcieCores ();
 
   InLpm = TRUE;
 
   return Status;
}

/***************************************************************************//**
 * @fn PcieConfigLibLowBattChargingHandler
 * @brief LPM callback function 
 *
 * Callback function to handle low power mode entry and exit for PCIe

 * @param  CodeType             Indicates the type of status code being
 *                              reported.
 * @param  Value                Describes the current status of a hardware or
 *                              software entity. This included information about
 *                              the class and subclass that is used to classify
 *                              the entity as well as an operation.
 * @param  Instance             The enumeration of a hardware or software entity
 *                              within the system. Valid instance numbers start
 *                              with 1.
 * @param  CallerId             This optional parameter may be used to identify
 *                              the caller. This parameter allows the status code
 *                              driver to apply different rules to different
 *                              callers.
 * @param  Data                 This optional parameter may be used to pass
 *                              additional data.
 *
 * @retval EFI_SUCCESS          The function completed successfully.
 * @retval EFI_DEVICE_ERROR     Charger Protocol GUID not matched
 ******************************************************************************/
EFI_STATUS
EFIAPI PcieConfigLibLowBattChargingHandler (IN EFI_STATUS_CODE_TYPE   CodeType,
                                            IN EFI_STATUS_CODE_VALUE  Value,
                                            IN UINT32                 Instance,
                                            IN EFI_GUID               *CallerId,
                                            IN EFI_STATUS_CODE_DATA   *Data)
{
   LPM_EVENT_EXT_DATA * LpmEventData = NULL;
   BOOLEAN              bMatch       = FALSE;
   EFI_STATUS           Status       = EFI_UNSUPPORTED;

   if (((CodeType & EFI_STATUS_CODE_TYPE_MASK) != EFI_PROGRESS_CODE) || (Data == NULL))
      return Status;

   LpmEventData = (LPM_EVENT_EXT_DATA*)(Data + 1);
 
   bMatch = CompareGuid (&(LpmEventData->CalleeGuid), &gQcomDisplayPwrCtrlProtocolGuid);
 
   if (bMatch != TRUE)
      return EFI_UNSUPPORTED;
 
   switch (LpmEventData->LPMState)
   {
      case LPM_ENTRY:
        DEBUG ((EFI_D_WARN, "Entering charging\r\n"));

        // TODO: Revisit this logic, LPM is not required for Off mode, LPM mode is
        // not supported any more
        // Enter LPM only for off mode charging.
        if (IsDeviceInOffModeCharging ())
        {
           Status = PcieConfigLibLPMEnter();
           if (EFI_ERROR(Status))
              DEBUG ((EFI_D_WARN, "Enter LPM failed\r\n"));
        }
        else
          DEBUG ((EFI_D_WARN, "Not off mode charging, leave PCIe active\r\n"));
      break;
    
      case LPM_EXIT:
        /* Should never enter this case, as it is unsupported */
      break;
    
      default:
        DEBUG ((EFI_D_WARN, "Invalid LPM State\r\n"));
      break;
   }

   return Status;
}

EFI_STATUS
PcieConfigLibRegisterLowBattChargingCallBack (BOOLEAN InitType)
{
   EFI_STATUS                Status = EFI_SUCCESS;
   EFI_RSC_HANDLER_PROTOCOL *RscHandlerProtocol = NULL;

   Status = gBS->LocateProtocol (&gEfiRscHandlerProtocolGuid, NULL,
                                 (VOID **) &RscHandlerProtocol);

   if ((Status != EFI_SUCCESS) || (RscHandlerProtocol == NULL))
   {
      DEBUG ((EFI_D_WARN, "LocateRscProtocol Failed \r\n"));
      return Status;
   }

   if (InitType == REGISTER_CHG_CB)
      Status = RscHandlerProtocol->Register (PcieConfigLibLowBattChargingHandler, TPL_CALLBACK);
   else
      Status = RscHandlerProtocol->Unregister (PcieConfigLibLowBattChargingHandler);

   if (EFI_ERROR(Status))
      DEBUG ((EFI_D_WARN, "Register/UnRegister Batt chg cb failed\r\n"));

   return Status;
}

STATIC VOID EFIAPI
PcieConfigLibExitBSCallback (IN EFI_EVENT  Event,
                             IN VOID       *Context)
{
   /* Un register Rsc callback for Pcie Lpm */
   if (EFI_SUCCESS != PcieConfigLibRegisterLowBattChargingCallBack (UNREGISTER_CHG_CB))
      DEBUG ((EFI_D_WARN, "Unregister LPM callback FAILED\r\n"));
}


/*******************************************************************************
 *
 *            Public functions
 *
*******************************************************************************/

EFI_STATUS
PcieConfigLibSetupBattChargingHandler (VOID)
{
   EFI_STATUS      Status = EFI_SUCCESS;

   /* We don't need to register since we do NOT need to go into LPM for threshold
    * charging. For OffModeCharging we will not be initializing any ports, so,
    * we don't need to handle anything. Note that during Exit BS, EDK2 PCIBus driver
    * would be configured to turn off BME, so either the controller should be
    * accessible or none of the PCI handles should be active during that time. */
#if 0
   EFI_EVENT       ExitBsEvt;

   /* Register to turnoff PCIe in case of low battery charging */
   Status = PcieConfigLibRegisterLowBattChargingCallBack (REGISTER_CHG_CB);

   if (EFI_ERROR (Status))
      DEBUG ((EFI_D_WARN, "Low Battery callback failed\r\n"));


   Status = gBS->CreateEvent (EVT_SIGNAL_EXIT_BOOT_SERVICES, TPL_CALLBACK,
                              PcieConfigLibExitBSCallback, NULL, &ExitBsEvt);
   if (EFI_ERROR (Status))
      DEBUG ((EFI_D_WARN, "Register for EBS failed\r\n"));
#endif
   return Status;
}

BOOLEAN IsDeviceInOffModeCharging (VOID)
{
   EFI_STATUS Status = EFI_SUCCESS;
   BOOLEAN OffModeChg = FALSE;
   EFI_CHARGER_EX_PROTOCOL *ChgExIntf = NULL;

   Status = gBS->LocateProtocol (&gChargerExProtocolGuid, NULL,
                                 (void**)&ChgExIntf);

   if ((Status != EFI_SUCCESS) || (ChgExIntf == NULL))
      return FALSE;

   Status = ChgExIntf->IsOffModeCharging (&OffModeChg);
   if (Status != EFI_SUCCESS)
      return FALSE;

   return OffModeChg;
}


