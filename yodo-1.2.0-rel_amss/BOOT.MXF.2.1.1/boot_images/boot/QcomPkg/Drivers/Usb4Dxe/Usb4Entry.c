/** @file     Usb4PlatformRingIface.c 
    @brief    The USB4 Platform Specific Ring Interface.
    @details  
    @note     
    @ref      Copyright (c) 2020-2021 Qualcomm Technologies Incorporated.
              All Rights Reserved.
              Qualcomm Confidential and Proprietary.

    
**/

#include "Uefi.h"
#include <Protocol/EFIUsb4Config.h>
#include <Protocol/EFIPlatformInfo.h>
#include <Protocol/EFIChipInfo.h>
#include <Protocol/EFIUsb4Config.h>
#include <Protocol/EFIChargerEx.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiRuntimeServicesTableLib.h>

#include <Usb4Utils.h>
#include <Usb4Log.h>
#include "Usb4ClientUsb3.h"

#include "usb4_router.h"
#include "usb4_cm.h"

#include "Usb4InitDxe.h"
// Polling Interval for host router events.
#define USB4_EVENT_POLL_INTERVAL_MS_1   (10U)
#define USB4_EVENT_POLL_INTERVAL_MS_50  (50 * USB4_EVENT_POLL_INTERVAL_MS_1)

// USB4 global context
typedef struct _USB4_GLOBAL_CTX {
  EFI_HANDLE        Usb4ImageHandle;
  EFI_SYSTEM_TABLE* Usb4SystemTable;
  EFI_EVENT         Usb4ExitEvt;
  EFI_EVENT         Usb4TimerEvt;
  usb4_cm_ctx_t*    Cm[USB4_HR_SIZE];
  USB4_cfgParams_t cfgParams[USB4_HR_SIZE];             // [in] CM configuration parameters.  From container
} USB4_GC;

USB4_GC* Usb4GCtx   = NULL;

VOID
EFIAPI
Usb4TimerEventCb (
  IN EFI_EVENT Event,
  IN VOID *    Context
  )
{
  // TODO: AC figure out how to handle multiple core
  Usb4CmControlPacketHandler(((USB4_GC*)Context)->Cm[0]); 

#if 0
  USB4_GC* Usb4GCtx = (USB4_GC*) Context;
  USB4_HR_INST HrIdx;
  if (Usb4GCtx) {
    for (HrIdx = 0; HrIdx < USB4_HR_SIZE; HrIdx++) {
      Usb4CmPollEvts(Usb4GCtx->Cm[HrIdx]);
    }
  }
#endif
}


VOID
EFIAPI
Usb4Exit (
  IN EFI_EVENT Event,
  IN VOID*     Context
   )
{
#if 0
  EFI_STATUS Status = EFI_SUCCESS; 
#endif
  USB4_GC* Usb4GCtx = (USB4_GC*) Context;
#if 0
  USB4_HR_INST HrIdx;
#endif

  if (Usb4GCtx) {
// TODO: AC
#if 0
    for (HrIdx = 0; HrIdx < USB4_HR_SIZE; HrIdx++) {
      Status = Usb4CmUnInit(&Usb4GCtx->Cm[HrIdx]);
      if (Status != EFI_SUCCESS) {
        DEBUG ((EFI_D_ERROR, "Usb4DriverExitBootService: Failed to un-init CmInst %d, Status = %d\n", HrIdx, Status));
      }
    }
#endif

    if (Usb4GCtx->Usb4ExitEvt) {
      gBS->CloseEvent(Usb4GCtx->Usb4ExitEvt);
    } 

    if (Usb4GCtx->Usb4TimerEvt) {
      gBS->CloseEvent(Usb4GCtx->Usb4TimerEvt);
    } 
  }

  Usb4LogUnInit();
}

/**
  Entry point for EFI drivers.

  @param  ImageHandle       EFI_HANDLE.
  @param  SystemTable       EFI_SYSTEM_TABLE.

  @return EFI_SUCCESS       Success.
          EFI_DEVICE_ERROR  Fail.

**/

EFI_STATUS
EFIAPI
Usb4Entry (
  IN EFI_HANDLE           ImageHandle,
  IN EFI_SYSTEM_TABLE     *SystemTable
  )
{
  EFI_STATUS Status   = EFI_SUCCESS;
  USB4_HR_INST HrIdx  = USB4_HR_INVALID;
  USB4_PD_INFO pdInfo = {};
  USB4_cfgParams_t pParams = {0}; // VI initial settings structure
  UINT8      Usb4Enable = FALSE;
  UINTN      UefiVarSize = 0;
  EFI_CHARGER_EX_PROTOCOL       *pChargerExProtocol;
  BOOLEAN   gOffModeCharging = FALSE;
#ifndef USB4_LOAD_FIRMWARE_ONLY
  UINT32 connect_timeout_ms = 0;
  UINT32 idle_timeout_ms = 1000;
#endif // ~USB4_LOAD_FIRMWARE_ONLY

  UefiVarSize = sizeof(Usb4Enable);
  Status = gRT->GetVariable(L"EnableUsb4Uefi", &gQcomTokenSpaceGuid, NULL, &UefiVarSize, &Usb4Enable);
  if ((EFI_ERROR(Status)) || (FALSE == Usb4Enable)) {
    DEBUG ((EFI_D_ERROR, "Usb4Entry: skip due to Uefi var is disabled = %d\n", Usb4Enable));
    return EFI_SUCCESS;
  }
  
  //Check if the device is entering off mode charging
  Status = gBS->LocateProtocol(
           &gChargerExProtocolGuid,
           NULL,
           (VOID **) &pChargerExProtocol);

  if ((Status != EFI_SUCCESS) || (NULL == pChargerExProtocol))
  {
   DEBUG((EFI_D_INFO,"ERROR: UsbConfigInit - Failed to locate Charger Protocol! Error Code = 0x%08X\r\n", Status));
   gOffModeCharging = FALSE;
  }
  else
  {
	  if (pChargerExProtocol->IsOffModeCharging)
	  {
	    Status = pChargerExProtocol->IsOffModeCharging(&gOffModeCharging);
	  }
	  else
	  {
	    Status = EFI_UNSUPPORTED;
	  }
	  
	  if (Status != EFI_SUCCESS)
	  {
	    DEBUG((EFI_D_ERROR,"ERROR: UsbConfigInit - Failed to Off Mode Charging Error Code: %r \r\n", Status));
	    gOffModeCharging = FALSE;
	  }
  }
  
  //If Off mode charging enabled, skip USB4 init
  if (gOffModeCharging)
  {
  	DEBUG ((EFI_D_ERROR, "Usb4Entry: skipping since off mode charging enabled = %d\n", Usb4Enable));
    return EFI_SUCCESS;	
  }
  
  DEBUG ((EFI_D_ERROR, "Usb4Entry: usb4entry Not Skip\n", Usb4Enable));
  
  Usb4LogInit();

  Usb4GCtx = (USB4_GC*) AllocatePool(sizeof(USB4_GC));
  if(Usb4GCtx == NULL) {
    DEBUG ((EFI_D_ERROR, "Usb4Entry: Usb4GCtx Memory allocation Failed\n"));
    return EFI_OUT_OF_RESOURCES; 
  }

  gBS->SetMem(Usb4GCtx, sizeof(USB4_GC), 0);

  Usb4GCtx->Usb4ImageHandle = ImageHandle;
  Usb4GCtx->Usb4SystemTable = SystemTable;

  // TODO: AC initial static settings
  // TODO: AC Use array for multiple sets of settings
  // pParams.coreIndex = ; // Set inside the for loop
  pParams.bPollingMode = TRUE;
  pParams.bUseTBT3Mode = FALSE;
  pParams.bEnumerateLocalRouterOnly = TRUE;
  pParams.numLanes = 2;
  pParams.bDisableRS_FEC = FALSE;
  pParams.bLimitToGen2 = FALSE;
  pParams.bUseRealPD = TRUE; // This is required when PD from PMIC is ready
  pParams.bToggleTypeC = TRUE;
  pParams.bUSB4DriverLoaded = TRUE;
  pParams.controlPacketsTimeout_ms = 0x2000;
  pParams.tmuMode = USB4_TMU_MODE_NOT_SET;

#if 0
  BOOLEAN bPCIeEP;                    /**< If true, configure PCIe AP as EP */
  BOOLEAN bUSB3Device;                /**< If true, configure USB3 AP as device */
  BOOLEAN bSkipH2HHIArings;           /**< If true, SkipH2HHIA Rings */
  BOOLEAN bUSB3DriverLoaded;          /**< If true, build USB3 path, and update PM that initialization done from this SS */
  BOOLEAN bPCIeDriverLoaded;          /**< If true, build PCIe path, and update PM that initialization done from this SS  */
  BOOLEAN bDPDriverLoaded;            /**< If true, build DP path, and update PM that initialization done from this SS  */
  BOOLEAN bUSB4DriverLoaded;          /**< If true, update PM that initialization done from USB4 test  */
#endif

  for (HrIdx = 0; HrIdx < USB4_HR_SIZE; HrIdx++) {
    pParams.coreIndex = HrIdx;
    Usb4GCtx->Cm[HrIdx] = usb4_mem_alloc(sizeof(usb4_cm_ctx_t), 0);
    Usb4CmInit(Usb4GCtx->Cm[HrIdx], HrIdx);

    Usb4CmConfig(Usb4GCtx->Cm[HrIdx], &pParams);
  }

  // Needed to defer CM Enable since firmware is loaded with 1 PIL call in HYP
  for (HrIdx = 0; HrIdx < USB4_HR_SIZE; HrIdx++) {
    Usb4CmEnable(Usb4GCtx->Cm[HrIdx]);
  }

#if 0 // TODO: AC Verify if this is causes a crash
  Status = Usb4InitDriverEntryPoint(Usb4GCtx->Usb4ImageHandle);
  if (Status != EFI_SUCCESS) {
    Usb4Log1(USB4_LOG_ERR, Usb4Entry__Err_Failed_to_initialize_ClientDxe__Status, 0, Status);
  }
#endif

  Usb4ClientInit();


  /* Set some defaults in case not real PD is used */
  pdInfo.current_mode = USB4_PD_ATTACH_MODE_USB4;
  pdInfo.CurrentMode = USB4_PD_ATTACH_MODE_USB4;
  pdInfo.CableGen = USB4_PD_CABLE_GEN_3;
  pdInfo.cable_type = USB4_PD_CABLE_TYPE_PASSIVE;
  pdInfo.CableType = USB4_PD_CABLE_TYPE_PASSIVE;

#if 1
// +++ initial test
  pdInfo.cc_orientation = USB4_PD_CC_ORIENTATION_OPEN;
  pdInfo.CcOrientation = USB4_PD_CC_ORIENTATION_OPEN; 
// --- initial test
#endif

#if 0
  // +++ Test HSE without PD
  pdInfo.cc_orientation = USB4_PD_CC_ORIENTATION_CC1;
  pdInfo.CcOrientation = USB4_PD_CC_ORIENTATION_CC1; 
  // --- Test HSE without PD
#endif

  if (TRUE == pParams.bUseTBT3Mode)
  {
      pdInfo.current_mode = USB4_PD_ATTACH_MODE_TBT3;
  }

#ifndef USB4_LOAD_FIRMWARE_ONLY  
  /* Short timeout to handle DP IN Adapter port Hot plug
     running the state machine in polling mode will wait all the 
     time */
  connect_timeout_ms = pParams.controlPacketsTimeout_ms;
  if (0 == connect_timeout_ms)
  {
      connect_timeout_ms = 100;
  }
  
  if (pParams.bEnumerateLocalRouterOnly)
  {        
      if (0 != Usb4CmNotifyUsb4CableEvent(Usb4GCtx->Cm[0], &pdInfo))
      {
          USB4_ERROR_STACK(-1);
      }
      if (0 != Usb4CmNotifyUsb4CableEvent(Usb4GCtx->Cm[1], &pdInfo))
      {
          USB4_ERROR_STACK(-1);
      }

#if 1    
      /* Short timeout to handle DP IN Adapter port Hot plug */
      USB4_ASSERT(0 == Usb4CmWaitForHostConnectStateMachine(Usb4GCtx->Cm[0], connect_timeout_ms, 
                                                                              idle_timeout_ms));
#endif
  }
  // TODO: AC port rest of the code from container



  // Register for boot services exit event.
  Status = gBS->CreateEventEx(EVT_NOTIFY_SIGNAL, TPL_CALLBACK, Usb4Exit, Usb4GCtx, &gEfiEventExitBootServicesGuid, 
    &Usb4GCtx ->Usb4ExitEvt);
  if (Status != EFI_SUCCESS) {
    Usb4Log1(USB4_LOG_ERR, Usb4Entry__Err_Failed_to_register_exit_event__Status, 0, Status);
  }

  // Create a timer to poll USB4 events
  Status = gBS->CreateEvent(EVT_TIMER | EVT_NOTIFY_SIGNAL, TPL_CALLBACK, Usb4TimerEventCb, Usb4GCtx, 
    &Usb4GCtx->Usb4TimerEvt);
  if (Status != EFI_SUCCESS) {
    Usb4Log1(USB4_LOG_ERR, Usb4Entry__Err_Failed_to_create_timer_event__Status, 0, Status);
  }

  // Signal the event immediately.
  gBS->SignalEvent(Usb4GCtx->Usb4TimerEvt);

  Status = gBS->SetTimer(Usb4GCtx->Usb4TimerEvt, TimerPeriodic, USB4_EVENT_POLL_INTERVAL_MS_50);
  if (Status != EFI_SUCCESS) {
    Usb4Log1(USB4_LOG_ERR, Usb4Entry__Err_Failed_to_set_timer__Status, 0, Status);
  }
#endif // ~USB4_LOAD_FIRMWARE_ONLY
  return Status;
}

