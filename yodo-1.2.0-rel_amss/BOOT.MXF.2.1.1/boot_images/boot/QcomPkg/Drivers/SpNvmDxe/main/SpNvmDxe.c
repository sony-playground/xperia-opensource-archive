/**
 * @file  SpNvmDxe.c 
 *  
 * Dxe driver for SP NVM in UEFI  
 */

/*=============================================================================
 Copyright (c) 2020-2021 Qualcomm Technologies, Incorporated.
 All rights reserved.
 Qualcomm Technologies, Confidential and Proprietary.
=============================================================================*/

/*=============================================================================
                    EDIT HISTORY FOR FILE


 when       who     what, where, why
 --------   ---     -----------------------------------------------------------
 07/29/21   vp      Logging improvements
 05/17/21   sn      Register chargerapp LPMExit cb only when real battery is present
 04/19/21   av      Open sTPM nvm channel only if TPM type is sTPM
 02/26/21   sn      Ignore charging status when platform type is CDP or RUMI
 02/11/21   sn      Delay sp_nvm init based on charging status
 02/08/21   vp      Fix stpm channel name
 05/30/20   ll      initial release
=============================================================================*/

/*===========================================================================
                    INCLUDE FILES                                            
===========================================================================*/
#include "osCommon.h"
#include "nvm_main.h"
#include <Uefi.h>
#include <Library/UefiBootServicesTableLib.h>
#include "QcomLib.h"
#include <Library/QcomBaseLib.h> 
#include <Library/DebugLib.h>
#include <Library/BaseMemoryLib.h>
#include <stdio.h>
#include <Include/Lpm.h>

/** Protocol Dependencies */
#include <Protocol/EFISpNvm.h>
#include <Protocol/EFIChargerEx.h>
#include <Protocol/ReportStatusCodeHandler.h>
#include <Protocol/EFITpmControl.h>

/*===========================================================================
                    GLOBAL VARIABLE DECLARATIONS                              
===========================================================================*/
UINT32 tpmType = None;

/*===========================================================================
                    LOCAL VARIABLE DECLARATIONS                              
===========================================================================*/

const char *supportedAppNamesSTPM[] = {
    "sp_nvm",
    "stpm_lite_msft",
};

const int spss_nvm_app_names_stpm_count_ = 2;

const char *supportedAppNames[] = {
    "sp_nvm",
};

const int spss_nvm_app_names_count_ = 1;

EFI_SPNVM_PROTOCOL SpNvmProtocolImplementation;

/* Exit Boot Services vars */
extern EFI_GUID gEfiEventExitBootServicesGuid;
EFI_EVENT SpNvmExitBSEvent = (EFI_EVENT)NULL;

#define EFI_FAILURE (80)

/*===========================================================================*/
/*                  FUNCTIONS PROTOTYPES                                     */
/*===========================================================================*/

STATIC EFI_STATUS SpNvmRegisterLPMCb(BOOLEAN register_Lpm);
STATIC EFI_STATUS SpNvmLPMCb (
    IN EFI_STATUS_CODE_TYPE     CodeType,
    IN EFI_STATUS_CODE_VALUE    Value,
    IN UINT32                   Instance,
    IN EFI_GUID                 *CallerId,
    IN EFI_STATUS_CODE_DATA     *Data OPTIONAL
    );
STATIC VOID SpNvmExitBSCb(EFI_EVENT event,void *context);
STATIC EFI_STATUS SpNvmRegisterEBSCb(VOID);
/*===========================================================================
                    EXTERNAL FUNCTION DEFINITIONS                                     
===========================================================================*/
/**
 * Entry point for the SP NVM Dxe driver.
 * Initialize SpNvm Module. Calls startRoutine for each channel/apps
 * (nvm_main.cpp: nvm_main(appNames[], apps_num))
 *
 * 
 * @return Standard EFI error codes
 */
EFI_STATUS
sp_nvm_entry_point (IN EFI_HANDLE ImageHandle, IN EFI_SYSTEM_TABLE *SystemTable)
{
  EFI_STATUS                status                   = EFI_SUCCESS;
  EFI_CHARGER_EX_PROTOCOL   *pChargerExProtocol      = NULL;
  EFI_CHARGER_EX_FLASH_INFO sPowerTypeInfo           = {0};
  BOOLEAN bBatteryPresent                            = FALSE;
  UINT32                    tpmState                 = None;
  QCOM_TPM_CONTROL_PROTOCOL *pQcomTpmControlProtocol = NULL;

  fileSystemInit();

  if (EFI_SUCCESS != gBS->LocateProtocol( &gQcomTpmControlProtocolGuid,
                                          NULL,
                                             (VOID **)&pQcomTpmControlProtocol ))
  {
     // Unable to locate TpmControl protocol
     LOGE("%a: Unable to locate tpm control protocol\r\n", __func__);    
     return EFI_NOT_FOUND;
  }

  if (EFI_SUCCESS != pQcomTpmControlProtocol->GetTpmStateAndType( pQcomTpmControlProtocol, 
                                                                  &tpmState, 
                                                                     &tpmType ))
  {
     LOGE("%a: Unable to get TPM type\r\n", __func__);    
     return EFI_NOT_FOUND;
  }

   //locate ChargerEx protocol to get charging status
  if (EFI_SUCCESS != gBS->LocateProtocol(&gChargerExProtocolGuid,
                                  NULL,
                                  (void**)&pChargerExProtocol))
  {
     // Unable to locate charger protocol
     LOGE("%a: Unable to locate charger protocol\r\n", __func__);
     return EFI_NOT_FOUND;
  }
  
  status = pChargerExProtocol->IsPowerOk(EFI_CHARGER_EX_POWER_FLASH_BATTERY_VOLTAGE_TYPE, &sPowerTypeInfo);
  
  if(EFI_UNSUPPORTED == status )
  {
      //ChargerDxe does not support battery status query for CDP and RUMI
      //platform types. For such platforms, proceed with initialisation
      //ignoring the charging/battery status
      if(tpmType == sTPM)
      {
          status = nvm_main (supportedAppNamesSTPM, spss_nvm_app_names_stpm_count_);
      }
      else
      {
          status = nvm_main (supportedAppNames, spss_nvm_app_names_count_);
      }
      LOGI("%a: SpNvm_init success\r\n", __func__);
      return status;
  }
   
  if (EFI_SUCCESS != status)
  {
      // Unable to get the status
      LOGE("%a: Unable to get the IsPowerOk status\r\n", __func__);
      return EFI_FAILURE;
  }

  status = pChargerExProtocol->GetBatteryPresence(&bBatteryPresent);
  if(status != EFI_SUCCESS )
  {
      //Unable to get the status
      LOGE("%a: Unable to get GetBatteryPresence status: %d\r\n", __func__, status);
      return  EFI_FAILURE;
  }
  if(bBatteryPresent == FALSE)
  {
      //Battery is not present ,don't proceed further
      LOGI("%a: Battery is not present Do not proceed SPNVM_init \r\n", __func__);
      return EFI_FAILURE;
  }
  else
  {
      if(sPowerTypeInfo.bCanFlash == TRUE)
      {
          //if we reach here battery is present with charging status is above thresholds.
          //or Fake battery i.e Device is debug board platform
          LOGI("%a: proceed secnvm init\r\n", __func__);
          if(tpmType == sTPM)
          {
              status = nvm_main (supportedAppNamesSTPM, spss_nvm_app_names_stpm_count_);
          }
          else
          {
              status = nvm_main (supportedAppNames, spss_nvm_app_names_count_);
          }
          
          return status;
      }
      else
      {
          //Battery is present and Charging status is below threshold. Register for LPM events
          //ChargerApp broadcast LPM events when real battery is present
          status = gBS->InstallMultipleProtocolInterfaces (
                &ImageHandle,
                &gEfiSpNvmProtocolGuid,
                &SpNvmProtocolImplementation,
                NULL);
          if(status != EFI_SUCCESS)
          {
              LOGE("%a: InstallMultipleProtocolInterfaces failed: %d\r\n", __func__,status);
              return status;
          }
          status = SpNvmRegisterLPMCb(TRUE);
          if(status != EFI_SUCCESS)
          {
              LOGE("Register for LPM events Failed,Status :%d\r\n",status);
              return status;  
          }
          status = SpNvmRegisterEBSCb();
          if(status != EFI_SUCCESS)
          {
              LOGE("Register for ExitBootServices event Failed,Status :%d\r\n",status);
              return status;
          }
          LOGI("Charging status less than thresholds, SPNVMdxe Register for LPM,EBS events Success\r\n");
      }
  }
  return status;
}

/** 
  SpNvmRegisterLPMCb
  
  @brief
  Register/Un-register for LPM Events
*/
EFI_STATUS SpNvmRegisterLPMCb(BOOLEAN register_Lpm)
{
  EFI_STATUS               Status                 = EFI_SUCCESS;
  EFI_RSC_HANDLER_PROTOCOL *pRscHandlerProtocol   = NULL;

  Status = gBS->LocateProtocol(&gEfiRscHandlerProtocolGuid, NULL, (VOID **) &pRscHandlerProtocol);
  
  if((EFI_SUCCESS == Status) && (pRscHandlerProtocol != NULL))
  {
     if(register_Lpm == TRUE)
     {
        Status = pRscHandlerProtocol->Register(SpNvmLPMCb, TPL_CALLBACK);
     }
     else
     {
        Status = pRscHandlerProtocol->Unregister(SpNvmLPMCb); 
     }
  }
  else
  {
     LOGE("%a: Locate protocol Failed,Status:%d\r\n", __func__, Status); 
  }
  return Status;
}

/** 
  SpNvmLPMCb
  
  @brief
  LPM callback Function ,processing LPM_EXIT event
*/
EFI_STATUS
EFIAPI SpNvmLPMCb (
  IN EFI_STATUS_CODE_TYPE   CodeType,
  IN EFI_STATUS_CODE_VALUE  Value,
  IN UINT32                 Instance,
  IN EFI_GUID               *CallerId,
  IN EFI_STATUS_CODE_DATA   *Data
  )
{
  LPM_EVENT_EXT_DATA * pLpmEventData = NULL;
  BOOLEAN              bMatch        = FALSE;
  EFI_STATUS           Status        = EFI_UNSUPPORTED;

  if (((CodeType & EFI_STATUS_CODE_TYPE_MASK) == EFI_PROGRESS_CODE ) &&
      (Data != NULL))
  {
    pLpmEventData = (LPM_EVENT_EXT_DATA*)( Data + 1);

      bMatch = CompareGuid(&(pLpmEventData->CalleeGuid), &gEfiClockProtocolGuid);
    if (bMatch == TRUE)
    {
      switch (pLpmEventData->LPMState)
      {
        case LPM_EXIT:
               LOGI("%a: LPM_EXIT Received,proceed sec_nvm Init\r\n", __func__);
               if(tpmType == sTPM)
               {
                 Status = nvm_main (supportedAppNamesSTPM, spss_nvm_app_names_stpm_count_);
               }
               else
               {
                 Status = nvm_main (supportedAppNames, spss_nvm_app_names_count_);
               }
        break;
        default:
               LOGE("%a: Invalid LPM State\r\n", __func__);
        break;
      }
    }
  }

  return Status;
}

/** 
  SpNvmRegisterEBSCb
  
  @brief
  Register for BootServices Exit event.
*/
STATIC EFI_STATUS SpNvmRegisterEBSCb(VOID)
{
   //Register to Exit Boot Service Event
   return gBS->CreateEventEx (EVT_NOTIFY_SIGNAL,
                      TPL_CALLBACK,
                      SpNvmExitBSCb,
                      NULL,
                      &gEfiEventExitBootServicesGuid,
                      &SpNvmExitBSEvent);
}

/** 
  SpNvmExitBSCb
  
  @brief
  Exit BootServices event cb.
*/
STATIC VOID SpNvmExitBSCb (
  EFI_EVENT        Event,
  VOID             *Context
  )
{
   EFI_STATUS           Status       = EFI_FAILURE;

   Status = SpNvmRegisterLPMCb(FALSE); 
   if(Status != EFI_SUCCESS)
   {
      LOGE("%a:UnRegister for LPM events Failed,Status: %d\r\n",__func__,Status);  
   }
   LOGI("%a: Received ExitBS cb and UnRegister for LPMcb success:%d\r\n",__func__);
}

/** 
  SPNVM Protocol implementation 
*/
EFI_SPNVM_PROTOCOL SpNvmProtocolImplementation =
{
   SPNVM_REVISION,
};
