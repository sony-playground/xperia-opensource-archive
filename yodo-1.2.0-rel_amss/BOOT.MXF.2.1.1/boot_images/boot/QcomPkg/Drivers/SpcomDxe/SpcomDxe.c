/**
 @file  SpcomDxe.c
 */
/*=============================================================================
 Copyright (c) 2020-2021 Qualcomm Technologies, Incorporated.
 All rights reserved.
 Qualcomm Technologies, Confidential and Proprietary.
 =============================================================================*/

/*=============================================================================
 EDIT HISTORY


 when       who     what, where, why
 --------   ---     -----------------------------------------------------------
 07/29/21   vp      Logging improvements
 05/17/21   sn      Register chargerapp LPMExit cb only when real battery is present
 04/14/21   nc      spcom_unregister_client crash fix
 02/24/21   vp      Add EFI_Spcom_PollNvmCh api
 02/26/21   sn      Ignore charging status when platform type is CDP or RUMI
 02/11/21   sn      Delay spcom_init based on charging status
 01/11/21   vp      Load API's fix
 06/15/20   vp      initial release
 =============================================================================*/

/*===========================================================================*/
/*                  INCLUDE FILES                                            */
/*===========================================================================*/
#include <Uefi.h>
#include <Include/Lpm.h>
/**
 Library Dependencies
 */
#include <Library/QcomLib.h>
#include <Library/QcomBaseLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/DebugLib.h>
#include <Library/BaseMemoryLib.h>

/**
 Protocol Dependencies
 */
#include <Protocol/EFIGLink.h>
#include <Protocol/EFISpcom.h>
#include "spcom.h"
#include <Protocol/EFIChargerEx.h>
#include <Protocol/ReportStatusCodeHandler.h>

/*===========================================================================*/
/*                  LOCAL VARIABLE DECLARATIONS                              */
/*===========================================================================*/
EFI_SPCOM_PROTOCOL SpcomProtocolImplementation;
/* Exit Boot Services vars */
extern EFI_GUID gEfiEventExitBootServicesGuid;
EFI_EVENT SpcomExitBSEvent = (EFI_EVENT)NULL;

#define EFI_FAILURE (80)

/*===========================================================================*/
/*                  FUNCTIONS PROTOTYPES                                     */
/*===========================================================================*/
STATIC VOID SpcomBSCb(EFI_EVENT Event,void *context);
STATIC EFI_STATUS SpcomRegisterLPMCb(BOOLEAN register_Lpm);
STATIC EFI_STATUS Spcom_LPMCb (
    IN EFI_STATUS_CODE_TYPE     CodeType,
    IN EFI_STATUS_CODE_VALUE    Value,
    IN UINT32                   Instance,
    IN EFI_GUID                 *CallerId,
    IN EFI_STATUS_CODE_DATA     *Data OPTIONAL
    );
STATIC EFI_STATUS SpcomRegisterEBSCb(VOID);

/*===========================================================================*/
/*                  FUNCTION DEFINITIONS                                     */
/*===========================================================================*/
/**
 Initialize Spcom Module

 @param none

 @return
 EFI_SUCCESS:                  Function returned successfully.
 EFI_INVALID_PARAMETER:        A Parameter was incorrect.
 EFI_DEVICE_ERROR:             The physical device reported an error.
 EFI_UNSUPPORTED:              The physical device does not support this function
 */
EFI_STATUS
Spcom_Init (IN EFI_HANDLE ImageHandle, IN EFI_SYSTEM_TABLE *SystemTable)
{
   EFI_STATUS status                              = EFI_SUCCESS;
   EFI_CHARGER_EX_PROTOCOL   *pChargerExProtocol  = NULL;
   EFI_CHARGER_EX_FLASH_INFO sPowerTypeInfo       = {0};
   BOOLEAN bBatteryPresent                        = FALSE;

   //locate ChargerEx protocol to get charging status
   if (EFI_SUCCESS != gBS->LocateProtocol(&gChargerExProtocolGuid,
                                  NULL,
                                  (void**)&pChargerExProtocol))
   {
      //Unable to locate charger protocol
      LOGE("%a: Unable to locate charger protocol\r\n", __func__);
      return EFI_NOT_FOUND;
   }
   
   status = pChargerExProtocol->IsPowerOk(EFI_CHARGER_EX_POWER_FLASH_BATTERY_VOLTAGE_TYPE, &sPowerTypeInfo);
   if(EFI_UNSUPPORTED == status)
   {
      //ChargerDxe does not support battery status query for CDP and RUMI
      //platform types. For such platforms, proceed with initialisation
      //ignoring the charging/battery status
      status = gBS->InstallMultipleProtocolInterfaces (
                  &ImageHandle, 
                  &gEfiSpcomProtocolGuid,
                  &SpcomProtocolImplementation,
                  NULL);
      status = spcom_init ();
      LOGI("%a: spcom_init success\r\n", __func__);
      return status;
    }

   if (EFI_SUCCESS != status)
   {
      //Unable to get the status
      LOGE("%a: Unable to get the IsPowerOk status :%d\r\n", __func__, status);
      return EFI_FAILURE;
   }
   status = pChargerExProtocol->GetBatteryPresence(&bBatteryPresent);
   if(status != EFI_SUCCESS )
   {
      //Unable to get the status
      LOGE("%a: Unable to get GetBatteryPresence status: %d \r\n", __func__, status);
      return  EFI_FAILURE;
   }
   if(bBatteryPresent == FALSE)
   {
      //Battery is not present ,don't proceed further
      LOGE("%a: Battery is not present Do not proceed spcom_init \r\n", __func__);
      return EFI_FAILURE;
   }
   else
   { 
      if(sPowerTypeInfo.bCanFlash == TRUE)
      {
         //if we reach here battery is present with charging status is above thresholds.
         //or Fake battery i.e Device is debug board platform
    	 LOGI("%a: bCanFlash TRUE, Proceed spcom_init\r\n", __func__);
         status = gBS->InstallMultipleProtocolInterfaces (
                     &ImageHandle, 
                     &gEfiSpcomProtocolGuid,
                     &SpcomProtocolImplementation,
                     NULL);
         status = spcom_init ();
         return status; 
      }
      else
      {
         //Battery is present and Charging status is below threshold. Register for LPM events
         //ChargerApp broadcast LPM events when real battery is present
         status = gBS->InstallMultipleProtocolInterfaces (
                     &ImageHandle, 
                     &gEfiSpcomProtocolGuid,
                     &SpcomProtocolImplementation,
                     NULL);
         if(status != EFI_SUCCESS)
         {
            LOGE("%a: InstallMultipleProtocolInterfaces failed: %d\r\n", __func__,status);
            return status;
         }
         status = SpcomRegisterLPMCb(TRUE);
         if(status != EFI_SUCCESS)
         {
            LOGE("Register for LPM events Failed,Status: %d\r\n",status);
            return status;  
         } 
         status = SpcomRegisterEBSCb();
         if(status != EFI_SUCCESS)
         {
            LOGE("Register for ExitBootServices event Failed,Status: %d\r\n",status);
            return status;
         }
         LOGI("Charging status less than thresholds, SPCOMdxe Register for LPM,EBS events Success\r\n");
      }
   }
#ifdef SPCOMDXE_SANITY_TEST
   if (spcom_is_sp_subsystem_link_up ())
   {
      status = spcom_sanity_test ();
   }
   else
   {
      status = EFI_TIMEOUT;
   }
#endif
   return status;
}

/** 
  SpcomRegisterLPMCb
  
  @brief
  Register/Un-register for LPM Events
*/
EFI_STATUS SpcomRegisterLPMCb(BOOLEAN register_Lpm)
{
  EFI_STATUS               Status                 = EFI_SUCCESS;
  EFI_RSC_HANDLER_PROTOCOL *pRscHandlerProtocol   = NULL;

  Status = gBS->LocateProtocol(&gEfiRscHandlerProtocolGuid, NULL, (VOID **) &pRscHandlerProtocol);
  
  if((EFI_SUCCESS == Status) && (pRscHandlerProtocol != NULL))
  {
     if(register_Lpm == TRUE)
     {
        Status= pRscHandlerProtocol->Register(Spcom_LPMCb, TPL_CALLBACK);
     }
     else
     {
        Status= pRscHandlerProtocol->Unregister(Spcom_LPMCb);
     }
  }
  else
  {
     LOGE("%a: Locate protocol Failed,Status :%d\r\n",__func__,Status); 
  }
  return Status;
}

/** 
  Spcom_LPMCb
  
  @brief
  LPM callback Function ,processing LPM_EXIT event
*/
EFI_STATUS
EFIAPI Spcom_LPMCb (
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
        	  LOGI("%a: LPM_EXIT Received, Proceed spcom_init\r\n", __func__);
              Status = spcom_init ();
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
  SpcomRegisterEBSCb
  
  @brief
  Register for BootServices Exit event.
*/
STATIC EFI_STATUS SpcomRegisterEBSCb(VOID)
{
   //Register to Exit Boot Service Event
   return gBS->CreateEventEx (EVT_NOTIFY_SIGNAL,
                      TPL_CALLBACK,
                      SpcomBSCb,
                      NULL,
                      &gEfiEventExitBootServicesGuid,
                      &SpcomExitBSEvent);
}

/** 
  SpcomBSCb
  
  @brief
  Exit BootServices event cb.
*/
STATIC VOID SpcomBSCb (
  EFI_EVENT        Event,
  VOID             *Context
  )
{
   EFI_STATUS           Status       = EFI_FAILURE;

   Status = SpcomRegisterLPMCb(FALSE); 
   if(Status != EFI_SUCCESS)
   {
      LOGE("%a: UnRegister for LPM events Failed,Status:%d\r\n",__func__,Status);  
   }

   LOGI("%a: Received ExitBS cb and UnRegister for LPMcb success:%d\r\n",__func__);
}

EFI_STATUS
EFI_Spcom_IsAppLoaded (const char *ch_name)
{
   return spcom_is_app_loaded(ch_name);
}

EFI_STATUS
EFI_Spcom_IsSpssLinkUp (VOID)
{
   if (spcom_is_sp_subsystem_link_up ())
   {
      return EFI_SUCCESS;
   }
   else
   {
      return EFI_TIMEOUT;
   }
}

EFI_STATUS
EFI_Spcom_RegisterClient (struct spcom_client_info *info,
                          struct spcom_client **client)
{
   return spcom_register_client (info, client);
}

EFI_STATUS
EFI_Spcom_UnregisterClient (struct spcom_client **client)
{
   return spcom_unregister_client (client);
}

EFI_STATUS
EFI_Spcom_ClientSendMessage (struct spcom_client *client, void *req_ptr,
                             size_t req_size, void *resp_ptr,
                             size_t resp_size, size_t *rx_size,
                             size_t timeout_msec)
{
   return spcom_client_send_message_sync (client, req_ptr, req_size,
                                          resp_ptr, resp_size, rx_size,
                                          timeout_msec);
}

EFI_STATUS
EFI_Spcom_ClientIsServerConnected (struct spcom_client *client)
{
   if (spcom_client_is_server_connected (client))
   {
      return EFI_SUCCESS;
   }
   else
   {
      return EFI_NOT_FOUND;
   }
}

EFI_STATUS
EFI_Spcom_RegisterService (struct spcom_service_info *info,
                           struct spcom_server **server)
{
   return spcom_register_service (info, server);
}

EFI_STATUS
EFI_Spcom_UnregisterService (struct spcom_server *server)
{
   return spcom_unregister_service (server);
}

EFI_STATUS
EFI_Spcom_ServerGetNextRequest (struct spcom_server *server)
{
   return spcom_server_get_next_request (server);
}

EFI_STATUS
EFI_Spcom_LoadSpApp (const char *ch_name, EFI_GUID *appGuid, size_t image_size, size_t swap_size, size_t *load_resp_code)
{

   return spcom_load_app (ch_name, appGuid, image_size, swap_size, load_resp_code);
}

EFI_STATUS
EFI_Spcom_LoadSpAppFromBuffer (const char *ch_name,
                                 void *image_buf, size_t image_size,
                                 size_t swap_size, size_t *load_resp_code){
   return spcom_load_app_from_buffer(ch_name,
           image_buf, image_size, swap_size,load_resp_code);
}

EFI_STATUS
EFI_Spcom_Alloc (const char *ch_name, void **buf, size_t size)
{
   boolean app_load = false;
   return spcom_get_reserved_pil_region(ch_name, buf, size, app_load);
}

EFI_STATUS
EFI_Spcom_Free (const char *ch_name, void *buf, size_t size)
{
   boolean app_load = false;
   return spcom_clear_reserved_pil_region(ch_name, buf, size,app_load);
}

EFI_STATUS
EFI_Spcom_PollNvmCh (VOID)
{
   return poll_on_nvm_ch ();
}

/**
 SPCOM Protocol implementation
 */
EFI_SPCOM_PROTOCOL SpcomProtocolImplementation =
{
   SPCOM_REVISION,
   EFI_Spcom_IsAppLoaded,
   EFI_Spcom_IsSpssLinkUp,
   EFI_Spcom_RegisterClient,
   EFI_Spcom_UnregisterClient,
   EFI_Spcom_ClientSendMessage,
   EFI_Spcom_ClientIsServerConnected,
   EFI_Spcom_RegisterService,
   EFI_Spcom_UnregisterService,
   EFI_Spcom_ServerGetNextRequest,
   EFI_Spcom_LoadSpApp,
   EFI_Spcom_LoadSpAppFromBuffer,
   EFI_Spcom_Alloc,
   EFI_Spcom_Free,
   EFI_Spcom_PollNvmCh
};
