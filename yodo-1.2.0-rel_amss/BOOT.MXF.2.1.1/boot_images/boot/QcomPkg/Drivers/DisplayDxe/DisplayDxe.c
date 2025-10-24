/*=============================================================================
 
  File: DisplayDxe.c
 
  Display driver for UEFI
  
Copyright (c) 2010-2022 Qualcomm Technologies, Inc. All rights reserved.
Portions Copyright (c) 2007 - 2016, Intel Corporation. All rights reserved.<BR>
This program and the accompanying materials
are licensed and made available under the terms and conditions of the BSD License
which accompanies this distribution.  The full text of the license may be found at
http://opensource.org/licenses/bsd-license.php

THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
=============================================================================*/
#include <PiDxe.h>
#include <Uefi.h>
#include <Library/UefiLib.h>
#include <Library/UefiCfgLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/DebugLib.h>
#include <Library/PcdLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/CacheMaintenanceLib.h>
#include <Library/UncachedMemoryAllocationLib.h>
#include <Library/DxeServicesTableLib.h>
#include <Protocol/GraphicsOutput.h>
#include <Protocol/EFIChargerEx.h>
#include <Protocol/EFIPIL.h>
#include <Protocol/EdidActive.h>
#include <Library/BaseLib.h>
#include <Library/QcomBaseLib.h>
#include <Library/QcomLib.h>
#include "Protocol/EFIDisplayPwrCtrl.h"
#include "Protocol/EFIDisplayPwr.h"
#include "Protocol/EFIDisplayUtils.h"
#include "DisplayDxe.h"
#include "MDPLib.h"
#include "MDPSystem.h"
#include "DisplaySystem.h"
#include "DisplayUtils.h"
#ifdef FEATURE_XBOOT
#include "Protocol/EFIDisplay_X_target.h"
#endif /* FEATURE_XBOOT */

/**********************************************************************************************************************
 **   Macros/Defines
 **/
#define DISPLAY_TABLE_SIZE(_table_)          (sizeof(_table_)/sizeof((_table_)[0]))

/* Display Panel EDID Info Max Size*/
#define DISPLAY_EDID_ACTIVE_MAX_SIZE          256

/* Max supported width of Frame Buffer */
#define FRAMEBUFFER_MAX_WIDTH                 5120

/**********************************************************************************************************************
    Static/Globals
**/

EFI_EVENT EfiExitBootServicesEvent      = (EFI_EVENT)NULL;

/* Block IO Refresh Event */
EFI_EVENT gBlockIoRefreshEvt            = (EFI_EVENT) NULL;

/* Pil Services Event */
EFI_EVENT gPilServicesEvt               = (EFI_EVENT)NULL;

/* Pil services callback registration */
VOID     *gPilServicesRegistration      = NULL;

/* Display Init Event */
EFI_EVENT gDisplayInitEvent             = (EFI_EVENT)NULL;

/* Static information about the current display mode */
static DisplayDxe_ModeInfo   gDxeModeInfo;

/* Static information about panel EDID */
static uint8 gEDIDData[DISPLAY_EDID_ACTIVE_MAX_SIZE];

/* Display EDID Active Protocol */
static EFI_EDID_ACTIVE_PROTOCOL gEdidActiveProtocol;

/* Display DXE Protocol Blt Legacy function */
static EFI_STATUS
DisplayDxe_Blt_Legacy (
  IN  EFI_GRAPHICS_OUTPUT_PROTOCOL            *This,
  IN  EFI_GRAPHICS_OUTPUT_BLT_PIXEL           *BltBuffer,
  IN  EFI_GRAPHICS_OUTPUT_BLT_OPERATION       BltOperation,
  IN  UINTN                                   SourceX,
  IN  UINTN                                   SourceY,
  IN  UINTN                                   DestinationX,
  IN  UINTN                                   DestinationY,
  IN  UINTN                                   Width,
  IN  UINTN                                   Height,
  IN  UINTN                                   Delta);

/* Function table pointer to the supported protocol functions */
static EFI_GRAPHICS_OUTPUT_PROTOCOL gDisplayDxeOutputProtocol = {
    &DisplayDxe_QueryMode,
    &DisplayDxe_SetMode,
    &DisplayDxe_Blt_Legacy,
    &gDxeModeInfo.sProtocolInfo
};

/* DisplayDXE Device path */
static EFI_DISPLAY_DEVICE_PATH DisplayDevicePath = 
{
  {
    {
      HARDWARE_DEVICE_PATH,
      HW_VENDOR_DP,
      {
        (UINT8) (sizeof (VENDOR_DEVICE_PATH)),
        (UINT8) ((sizeof (VENDOR_DEVICE_PATH)) >> 8)
      }
    },
    EFI_GRAPHICS_OUTPUT_PROTOCOL_GUID
  },
  { END_DEVICE_PATH_TYPE, END_ENTIRE_DEVICE_PATH_SUBTYPE, {sizeof (EFI_DEVICE_PATH_PROTOCOL), 0}}
};

/* Default supported display list - TRUE: Enabled, FALSE: Disabled. */
bool32 gSupportedDisplayList[MDP_DISPLAY_MAX] =
{
  TRUE,   // MDP_DISPLAY_PRIMARY
  FALSE,  // MDP_DISPLAY_SECONDARY
  FALSE,  // MDP_DISPLAY_EXTERNAL
  FALSE,  // MDP_DISPLAY_EXTERNAL2
  FALSE,  // MDP_DISPLAY_EXTERNAL3
  FALSE,  // MDP_DISPLAY_EXTERNAL4
  FALSE,  // MDP_DISPLAY_EXTERNAL5
  FALSE   // MDP_DISPLAY_EXTERNAL6
};

/* Frame buffer Resolution Limit Table, table is landscape but check is done for both orientations. */
const MDP_ResolutionType gFBResLimit[] = 
{
    {5120, 2160},   // Index 0: 5k    ~42.4MB @ 32bpp
    {4096, 2160},   // Index 1: 4k    ~35.3MB @ 32bpp
    {3840, 2160},   // Index 2: UHD   ~33.1MB @ 32bpp
    {2560, 1440},   // Index 3: WQHD  ~14.7MB @ 32bpp
    {1920, 1280},   // Index 4: WUXGA  ~9.8MB @ 32bpp
    {1920, 1080},   // Index 5: FHD    ~8.2MB @ 32bpp
    {1280, 720},    // Index 6: HD     ~3.6MB @ 32bpp
};

/* Virtual mode table, list of additonal virtual modes exposed by the DisplayDxe */
const MDP_ResolutionType gVirtualResTable[] =
{
    {640,  480},   
    {800,  600},   
    {1280, 720},  
    {1024, 768},  
    {1280, 768},  
    {1366, 768}
};

/**********************************************************************************************************************
 **   Local function prototypes
 **/
/* Display power control protocol definition */
extern EFI_QCOM_DISPLAY_PWR_CTRL_PROTOCOL  gDisplayPwrCtrlProtocolImplementation;

/* Display power protocol definition */
extern EFI_DISPLAY_POWER_PROTOCOL  gDisplayPwrProtocolImplementation;

/* Display Utils protocol definition */
extern EFI_QCOM_DISPLAY_UTILS_PROTOCOL  gQcomDisplayUtilsProtocolImplementation;

/* Block IO Refresh GUID */
extern EFI_GUID gBlockIoRefreshGuid;

/* Pil GUID */
extern EFI_GUID gEfiPilProtocolGuid;

/* Select Mode */
static EFI_STATUS DisplayDxeSelectMode(MDP_Display_IDType eDisplayId, MDP_DetectParamType  *pDisplayModes);

/* Get charger power status */
static EFI_STATUS GetChargerPowerStatus(void);

/* Get the first available display id */
static MDP_Display_IDType GetFirstAvailableDisplayId(void);

/* Mode Set Thread */
static INT32 SetModeThread(void *sArgs);

/* Initialize the gSupportedDisplayList */
static bool32* DisplaySupportTableInit(void);

/* Display Blit function */
static void DisplayDxeBltInternal (
  UINT8   *pSrc,
  UINT8   *pDst,
  UINTN    uSrcX,
  UINTN    uSrcY,
  UINTN    uSrcWidth,
  UINTN    uSrcHeight,
  UINTN    uSrcStride,
  UINTN    uDstX,
  UINTN    uDstY,
  UINTN    uDstStride,
  UINTN    uBytesPerPixel
  );

/* Display Blit function for planar FSD format */
static void DisplayDxeBltInternalPlanar (
  UINT8   *pSrc,
  UINT8   *pDst,
  UINTN    uSrcX,
  UINTN    uSrcY,
  UINTN    uSrcWidth,
  UINTN    uSrcHeight,
  UINTN    uSrcStride,
  UINTN    uDstX,
  UINTN    uDstY,
  UINTN    uDstWidth,
  UINTN    uDstHeight,
  UINTN    uDstStride,
  UINTN    uBytesPerPixel
  );
  
static void DisplayDxeBlt (
  UINT8               *pSrc,
  UINT8               *pDst,
  UINTN                uSrcX,
  UINTN                uSrcY,
  UINTN                uSrcWidth,
  UINTN                uSrcHeight,
  UINTN                uSrcStride,
  UINTN                uDstX,
  UINTN                uDstY,
  UINTN                uDstWidth,
  UINTN                uDstHeight,
  UINTN                uDstStride,
  UINTN                uBytesPerPixel,
  MDP_PixelFormatType  ePixelFormat
  );

/* Display frame buffer Cache maintenance */
static void FlushStaleLines(VOID *pAddress, uint32 uLength);

/* Mode selection and filtering */
static EFI_STATUS DisplayDxeSetMode(
    MDP_Display_IDType    eDisplayId, 
    MDP_DetectParamType  *pDisplayModes,
    uint32 uFlags);

/* Register events callbacks */
static VOID DisplayDxeRegisterEvents(void);

/* Unregister events */
static VOID DisplayDxeUnRegisterEvents(void);

/* Update gSupportedDisplayList */
static VOID UpdateSupportedDisplayList(bool32 *pSupportedDisplay, uint32 uSupportedDisplayLength);

/* Divide by the frame buffer in to chunks based on number of inputs frame */
static VOID CalculateFrameBufferOffsets(UINT64 uFrameBufferBase, UINT64 uFrameBufferSize, FrameBufferOffsetType *pFrameBuffer, UINT32 uNumBuffers);

/* Get frame buffer info based on display ID */
static EFI_STATUS GetFrameBufferInfo(MDP_Display_IDType eDisplayId, FrameBufferOffsetType *pFrameBuffer);

//-------------------------------------------------------------------------------------------------
//  DisplayDxeExitBootServicesEvent
//
//  @brief
//      Callback function when UEFI Exit, free resources.
//
//  @params
//      [IN] Event
//          Event handle.
//      [IN] Context
//          Callback parameter context.
//
//  @return
//      None
//-------------------------------------------------------------------------------------------------
//
VOID EFIAPI DisplayDxeExitBootServicesEvent( IN EFI_EVENT  Event,  IN VOID *Context )
{
  uint32 uDxeExecTime    = 0;
  uint32 uDxeTotalTime   = 0;

  // Unregister events
  DisplayDxeUnRegisterEvents(); 

  //UEFI is shutting down - Handle it in MDP
  MDPExitBoot(gDxeModeInfo.uExitFlags);

  Display_Utils_BootExit(&uDxeExecTime, &uDxeTotalTime);
  DEBUG((EFI_D_WARN, "DisplayDxe: execution time(%dus) total time(%dus)\n", uDxeExecTime, uDxeTotalTime));
}


//-------------------------------------------------------------------------------------------------
//  BlockIoCallback
//
//  @brief
//      Callback function when GPT partition table is updated to invalidate all Block Io handles.
//
//  @params
//      [IN] Event
//          Event handle.
//      [IN] Context
//          Callback parameter context.
//
//  @return
//      None
//-------------------------------------------------------------------------------------------------
//
VOID EFIAPI BlockIoCallback(IN EFI_EVENT  Event, IN VOID *Context)
{
  /* GPT has been updated and the splash partition is invalid. So skip writing to it */
  gDxeModeInfo.uExitFlags |= MDP_EXIT_FLAG_INVALIDATE_GPT;
}



//-------------------------------------------------------------------------------------------------
//  UIActiveEventCallBack
//
//  @brief
//      Callback function when UI_Active event is signaled, turn on display
//
//  @params
//      [IN] Event
//          Event handle.
//      [IN] Context
//          Callback parameter context.
//
//  @return
//      None.
//-------------------------------------------------------------------------------------------------
//
VOID EFIAPI UIActiveEventCallBack( IN EFI_EVENT  Event, IN VOID *Context)
{
  EFI_DISPLAY_TYPE               eDisplayType = EFI_DISPLAY_TYPE_ALL;
  EFI_DISPLAY_POWER_CTRL_STATE   ePowerState  = EFI_DISPLAY_POWER_STATE_ON;

  /* Turn on the display */
  if (EFI_SUCCESS !=  EFI_DisplayPanelPowerControl(eDisplayType, ePowerState))
  {
    DEBUG((EFI_D_ERROR, "DisplayDxe: EFI_DisplayPanelPowerControl() failed to turn on display!\n"));
  }

}

//-------------------------------------------------------------------------------------------------
//  UIIdleEventCallBack
//
//  @brief
//      Callback function when UI_Idle event is signaled, turn off display
//
//  @params
//      [IN] Event
//          Event handle.
//      [IN] Context
//          Callback parameter context.
//
//  @return
//      None.
//-------------------------------------------------------------------------------------------------
//
VOID EFIAPI UIIdleEventCallBack( IN EFI_EVENT  Event, IN VOID *Context)
{
  EFI_DISPLAY_TYPE               eDisplayType = EFI_DISPLAY_TYPE_ALL;
  EFI_DISPLAY_POWER_CTRL_STATE   ePowerState  = EFI_DISPLAY_POWER_STATE_OFF;

  /* Turn off the display */
  if (EFI_SUCCESS !=  EFI_DisplayPanelPowerControl(eDisplayType, ePowerState))
  {
    DEBUG((EFI_D_ERROR, "DisplayDxe: EFI_DisplayPanelPowerControl() failed to turn off display!\n"));
  }

}

//-------------------------------------------------------------------------------------------------
//  PilServicesCallBack
//
//  @brief
//      Callback function to mount imagefv
//
//  @params
//      [IN] Event
//          Event handle.
//      [IN] Context
//          Callback parameter context.
//
//  @return
//      None.
//-------------------------------------------------------------------------------------------------
//
VOID EFIAPI PilServicesCallBack (IN EFI_EVENT  Event, IN VOID *Context)
{
  EFI_STATUS  eStatus      = EFI_SUCCESS;
  EFI_GUID    gFvNameGuid  = gEfiImageFvNameGuid;
  CHAR16     *pFvName      = L"ImageFv";

  if (EFI_SUCCESS != (eStatus = MDP_MountFv(gFvNameGuid, pFvName)))
  {
    DEBUG ((EFI_D_WARN, "DisplayDxe: Mount imagefv failed with status(%d)!\r\n", eStatus));
  }
}


//-------------------------------------------------------------------------------------------------
//  DisplayInitCallBack
//
//  @brief
//      Callback function for Display_Init event
//
//  @params
//      [IN] Event
//          Event handle.
//      [IN] Context
//          Callback parameter context.
//
//  @return
//      None.
//-------------------------------------------------------------------------------------------------
//
VOID EFIAPI DisplayInitCallBack( IN EFI_EVENT  Event, IN VOID *Context)
{
}


//-------------------------------------------------------------------------------------------------
//  DisplayDxeRegisterEvents
//
//  @brief
//      Register for event call backs
//
//  @params
//      none
//
//  @return
//      None.
//-------------------------------------------------------------------------------------------------
//
static VOID DisplayDxeRegisterEvents( void )
{
  EFI_GUID UIActiveEventGuid     = EFI_UI_ACTIVE_EVENT_GUID;
  EFI_GUID UIIdleEventGuid       = EFI_UI_IDLE_EVENT_GUID;
  EFI_GUID DisplayInitEventGuid  = EFI_DISPLAY_INIT_EVENT_GUID;
  UINT32   uImageFvSetting       = 0;

  /* Register for an ExitBootServicesEvent */
  if (EFI_SUCCESS != gBS->CreateEvent(EVT_SIGNAL_EXIT_BOOT_SERVICES, TPL_CALLBACK, DisplayDxeExitBootServicesEvent, NULL, &EfiExitBootServicesEvent))
  {
    DEBUG((EFI_D_WARN, "DisplayDxe: Failed to create EXIT_BOOT_SERVICES event!\n"));
  }

  /* Register for BlockIoRefreshEvent */
  if (EFI_SUCCESS != gBS->CreateEventEx(EVT_NOTIFY_SIGNAL, TPL_CALLBACK, BlockIoCallback, NULL, &gBlockIoRefreshGuid, &gBlockIoRefreshEvt))
  {
    DEBUG((EFI_D_WARN, "DisplayDxe: Failed to create BlockIoRefresh event!\n"));
  }

  /* Create and Register for UI_Active Event*/
  if (EFI_SUCCESS != gBS->CreateEventEx(EVT_NOTIFY_SIGNAL, TPL_CALLBACK, UIActiveEventCallBack, NULL, &UIActiveEventGuid, &gDxeModeInfo.UIActiveEvent))
  {
    DEBUG((EFI_D_WARN, "DisplayDxe: Failed to create UI_Active event!\n"));
  }
  
  /* Create and Register for UI_Idle Event*/
  if (EFI_SUCCESS != gBS->CreateEventEx(EVT_NOTIFY_SIGNAL, TPL_CALLBACK, UIIdleEventCallBack, NULL, &UIIdleEventGuid, &gDxeModeInfo.UIIdleEvent))
  {
    DEBUG((EFI_D_WARN, "DisplayDxe: Failed to create UI_Idle event!\n"));
  }

  /* Enable display imagefv based on the settings for runtime and compile time */
  if (((MDP_STATUS_OK  == MDP_Display_GetVariable_Integer(DISPVAR_ENABLE_DISPLAY_IMAGEFV, &uImageFvSetting))  &&
       (1              == uImageFvSetting))                                                                   ||
      ((MDP_STATUS_OK  == MDP_GetConfigValue(DISPVAR_ENABLE_DISPLAY_IMAGEFV_ASCII, &uImageFvSetting))         &&
       (1              == uImageFvSetting)))
  {
    /* Create and Register for pil services event */
    if (EFI_SUCCESS == gBS->CreateEvent(EVT_NOTIFY_SIGNAL, TPL_CALLBACK, PilServicesCallBack, NULL, &gPilServicesEvt))
    {
      if (EFI_SUCCESS != gBS->RegisterProtocolNotify(&gEfiPilProtocolGuid, gPilServicesEvt, (VOID *)&gPilServicesRegistration))
      {
        DEBUG((EFI_D_WARN, "DisplayDxe: Failed to register for pil services event!\n"));
      }
    }
  }

  /* Create and register for Display_Init event*/
  if (EFI_SUCCESS != gBS->CreateEventEx(EVT_NOTIFY_SIGNAL, TPL_CALLBACK, DisplayInitCallBack, NULL, &DisplayInitEventGuid, &gDisplayInitEvent))
  {
    DEBUG((EFI_D_WARN, "DisplayDxe: Failed to create Display_Init event!\n"));
  }

  if (EFI_SUCCESS != DisplayPwr_InitLPMSupport(TRUE))
  {
    DEBUG((EFI_D_WARN, "DisplayDxe: Failed to register LPM CB!\n"));
  }
}


//-------------------------------------------------------------------------------------------------
//  DisplayDxeUnRegisterEvents
//
//  @brief
//      Unregister events
//
//  @params
//      none
//
//  @return
//      None.
//-------------------------------------------------------------------------------------------------
//
static VOID DisplayDxeUnRegisterEvents( void )
{
  if ((NULL        != gDxeModeInfo.UIActiveEvent) &&
      (EFI_SUCCESS != gBS->CloseEvent(gDxeModeInfo.UIActiveEvent)))
  {
    DEBUG((EFI_D_ERROR, "DisplayDxe: Failed to Close event UI_Active\n"));
  }

  if ((NULL        != gDxeModeInfo.UIIdleEvent) &&
      (EFI_SUCCESS != gBS->CloseEvent(gDxeModeInfo.UIIdleEvent)))
  {
    DEBUG((EFI_D_ERROR, "DisplayDxe: Failed to Close event UI_Idle\n"));
  }

  if ((NULL        != gBlockIoRefreshEvt) &&
      (EFI_SUCCESS != gBS->CloseEvent(gBlockIoRefreshEvt)))
  {
    DEBUG((EFI_D_ERROR, "DisplayDxe: Failed to Close event BlockIORefresh\n"));
  }

  if ((NULL        != gPilServicesEvt) &&
      (EFI_SUCCESS != gBS->CloseEvent(gPilServicesEvt)))
  {
    DEBUG((EFI_D_ERROR, "DisplayDxe: Failed to close event for Pil Services\n"));
  }

  if ((NULL        != gDisplayInitEvent) &&
      (EFI_SUCCESS != gBS->CloseEvent(gDisplayInitEvent)))
  {
    DEBUG((EFI_D_ERROR, "DisplayDxe: Failed to Close event Display_Init\n"));
  }

  /* Un register LPM CB */
  if (EFI_SUCCESS != DisplayPwr_InitLPMSupport(FALSE))
  {
    DEBUG((EFI_D_WARN, "DisplayDxe: Failed to Unregister LPM CB!\n"));
  }
}

/**********************************************************************************************************************
     Public APIs
**/
/**
  Initialize the state information for the Display Dxe

  @param  ImageHandle   of the loaded driver
  @param  SystemTable   Pointer to the System Table

  @retval EFI_SUCCESS           Protocol registered
  @retval EFI_OUT_OF_RESOURCES  Cannot allocate protocol data structure
  @retval EFI_DEVICE_ERROR      Hardware problems

**/
EFI_STATUS
EFIAPI
#ifdef FEATURE_XBOOT
__DisplayDxeInitialize0
#else /* !FEATURE_XBOOT */
DisplayDxeInitialize
#endif /* !FEATURE_XBOOT */
  (
  IN EFI_HANDLE         ImageHandle,
  IN EFI_SYSTEM_TABLE   *SystemTable
  )
{
  EFI_STATUS              eStatus               = EFI_SUCCESS;
  EFI_GUID                sOutputGUID           = EFI_GRAPHICS_OUTPUT_PROTOCOL_GUID;
  EFI_HANDLE              hUEFIDisplayHandle    = NULL;
  MDP_InitParamsType      sInitParam;
  MDP_PropertiesParamType sDisplayProp;
  MDPPlatformParams       sPlatformParams;

  MDP_LOG_FUNC_ENTRY("DisplayDxeInitialize", 0x0);

  // Clear out global structures
  MDP_OSAL_MEMZERO(&gDxeModeInfo,    sizeof(DisplayDxe_ModeInfo));
  MDP_OSAL_MEMZERO(&sInitParam,      sizeof(MDP_InitParamsType));
  MDP_OSAL_MEMZERO(&sDisplayProp,    sizeof(MDP_PropertiesParamType));
  MDP_OSAL_MEMZERO(&sPlatformParams, sizeof(MDPPlatformParams));
  MDP_OSAL_MEMZERO(gEDIDData,        sizeof(gEDIDData));

#ifndef FEATURE_XBOOT
  /* Do display subsystem initialization here */
  DisplaySubsystemInitialization();
#endif /* !FEATURE_XBOOT */

  /* Register for all event callbacks */
  DisplayDxeRegisterEvents();

  sDisplayProp.pSupportedDisplayList = (bool32 (*)[MDP_DISPLAY_MAX])DisplaySupportTableInit();

  if (MDP_STATUS_OK != (eStatus = MDPPlatformConfigure(MDP_DISPLAY_PRIMARY, MDPPLATFORM_CONFIG_INIT, &sPlatformParams)))
  {
    DEBUG((EFI_D_ERROR, "DisplayDxe: MDPPlatformConfigure(MDPPLATFORM_CONFIG_INIT) failed!\n"));
  }
  else
  {
    // Initialize Apps BootLoader (ABL) interface
    // It checks for panel override, if any, set by ABL and sets up parameters which will be used by MDPInit
    if (MDP_STATUS_OK != MDPSetProperty(MDP_DISPLAY_PRIMARY, MDP_DISPLAY_PROPERTY_ABL_INTERFACE_INIT, &sDisplayProp))
    {
      DEBUG((EFI_D_INFO, "DisplayDxe: Failed to initialize ABL!\n"));
    }

    MDP_OSAL_MEMCPY(&sInitParam.aSupportedDisplays, &gSupportedDisplayList, sizeof(sInitParam.aSupportedDisplays));

    // Signal Display_Init event to set the display disabled list in the callback function.
    if (EFI_SUCCESS != gBS->SignalEvent(gDisplayInitEvent))
    {
      DEBUG((EFI_D_WARN, "DisplayDxe: Failed to send Display_Init event!\n"));
    }

    // Initialize the MDP 
    if (MDP_STATUS_OK != MDPInit(&sInitParam, MDP_INIT_FLAG_MMU_INIT))
    {
        DEBUG ((EFI_D_ERROR, "DisplayDxe: MDP init failed!\n"));      
        eStatus = EFI_DEVICE_ERROR;
    }
    else
    {
      MDP_PowerParamsType      sPowerParams;
      MDP_DetectParamType      sDetectParams;
      MDP_Display_IDType       eDisplayId = MDP_DISPLAY_PRIMARY;

      MDP_OSAL_MEMZERO(&sPowerParams, sizeof(MDP_PowerParamsType));
      MDP_OSAL_MEMZERO(&sDetectParams, sizeof(MDP_DetectParamType));

      sPowerParams.bPowerOn         = TRUE;
      sDisplayProp.bDisplayPwrState = TRUE;

      // Update gSupportedDisplayList since external display(MDP_DISPLAY_EXTERNAL) is configured in MDPInit()
      UpdateSupportedDisplayList(sInitParam.aSupportedDisplays, (sizeof(sInitParam.aSupportedDisplays) / sizeof(sInitParam.aSupportedDisplays[0])));

      ////////////////////////////////////////////
      // Primary / Secondary / External Display //
      ////////////////////////////////////////////

      // If the primary / secondary / External display is supported initialize it
      for (eDisplayId = MDP_DISPLAY_PRIMARY; eDisplayId <= MDP_DISPLAY_EXTERNAL; eDisplayId++)
      {
        if (FALSE == MDP_SUPPORTED_DISPLAY(eDisplayId))
        {
          continue;
        }
        else if (TRUE == Display_Utils_IsDisplayDisabled(eDisplayId))
        {
          // Display is set to disabled state, skip the MDP power operations but still update the display configuration info
          if (MDP_STATUS_OK != MDPGetProperty(eDisplayId, MDP_DISPLAY_PROPERTY_DISPLAY_CONFIG, &sDisplayProp))
          {
            DEBUG ((EFI_D_WARN, "DisplayDxe: Update display (%d) configuration info failed!\n", eDisplayId));
          }

          continue;
        }
        else if (MDP_STATUS_OK != MDPPower(eDisplayId, &sPowerParams, 0x0))
        {
          DEBUG ((EFI_D_WARN, "DisplayDxe: Common display panel power up failed!\n"));
        }
        else if (MDP_STATUS_OK != MDPDetect(eDisplayId, &sDetectParams, 0x0))
        {
          eStatus = EFI_DEVICE_ERROR;
        }
        // Passing NULL as the 3rd parameter since in this call this parameter is not being accessed
        else if (MDP_STATUS_OK != MDPGetProperty(eDisplayId, MDP_DISPLAY_PROPERTY_INTERFACE_AVAILABLE, NULL))
        {
          MDP_PowerParamsType sLocalPowerParams;

          MDP_OSAL_MEMZERO(&sLocalPowerParams, sizeof(sLocalPowerParams));

          sLocalPowerParams.bPowerOn        = FALSE;
          // Update gSupportedDisplayList for disabled interface
          gSupportedDisplayList[eDisplayId] = FALSE;

          // Power off display interface that is disabled
          if (MDP_STATUS_OK != MDPPower(eDisplayId, &sLocalPowerParams, POWERCONFIG_FLAGS_PANEL_POWER))
          {
            DEBUG ((EFI_D_WARN, "DisplayDxe: Specific display panel power down failed!\n")); 
          }
        }
        else if (MDP_STATUS_OK != MDPPower(eDisplayId, &sPowerParams, POWERCONFIG_FLAGS_PANEL_POWER))
        {
          DEBUG ((EFI_D_WARN, "DisplayDxe: Specific display panel power up failed!\n")); 
        }
        else if (TRUE == sDetectParams.bDisplayDetected)
        {
          // Add/filter any new modes according to resolution table and max resolution table.
          if (MDP_STATUS_OK != DisplayDxeSetMode(eDisplayId, &sDetectParams, 0x0))
          {
              DEBUG ((EFI_D_WARN, "DisplayDxe: Failed to add/filter new DisplayDxe modes!\n"));
          }

          // Set the display power state to on 
          if (MDP_STATUS_OK != MDPSetProperty(eDisplayId, MDP_DISPLAY_PROPERTY_POWER_STATE, &sDisplayProp))
          {
            eStatus = EFI_DEVICE_ERROR; 
          }

          // Get panel Edid info
          sDisplayProp.sEDID.pEdid = gEDIDData;
          sDisplayProp.sEDID.uSize = DISPLAY_EDID_ACTIVE_MAX_SIZE;

          if (MDP_STATUS_OK != MDPGetProperty(eDisplayId, MDP_DISPLAY_PROPERTY_GET_PANEL_EDID, &sDisplayProp))
          {
            gEdidActiveProtocol.Edid       = gEDIDData;
            gEdidActiveProtocol.SizeOfEdid = 0;
            DEBUG ((EFI_D_WARN, "DisplayDxe: Get Panel Edid failed %d\n", eDisplayId));
          }
          else
          {
            gEdidActiveProtocol.Edid       = gEDIDData;
            gEdidActiveProtocol.SizeOfEdid = sDisplayProp.sEDID.uSize;
          }
        }
      }

      //The information below applies only to the first valid display
      eDisplayId = GetFirstAvailableDisplayId();
	  
	  if (MDP_STATUS_OK != MDPGetProperty(eDisplayId, MDP_DISPLAY_PROPERTY_FRAMEBUFFER_INFO, &sDisplayProp))
	  {
	    DEBUG ((EFI_D_WARN, "DisplayDxe: get display (%d) framebuffer configuration info failed!\n", eDisplayId)); 
	  }

      // Default at some dummy mode
      gDxeModeInfo.sCurrentModeInfo.Version                       = GRAPHICS_OUTPUT_PROTOCOL_REVISION;
      gDxeModeInfo.sCurrentModeInfo.PixelFormat                   = DISPLAYDXE_DEFAULT_PIXEL_FORMAT;
      gDxeModeInfo.sCurrentModeInfo.HorizontalResolution          = 0;
      gDxeModeInfo.sCurrentModeInfo.VerticalResolution            = 0;
      gDxeModeInfo.sCurrentModeInfo.PixelInformation.RedMask      = DISPLAYDXE_RED_MASK;
      gDxeModeInfo.sCurrentModeInfo.PixelInformation.GreenMask    = DISPLAYDXE_GREEN_MASK;
      gDxeModeInfo.sCurrentModeInfo.PixelInformation.BlueMask     = DISPLAYDXE_BLUE_MASK;
      gDxeModeInfo.sCurrentModeInfo.PixelInformation.ReservedMask = DISPLAYDXE_ALPHA_MASK;
      gDxeModeInfo.sCurrentModeInfo.PixelsPerScanLine             = 0;
	  gDxeModeInfo.uFBPixelFormat                                 = sDisplayProp.sModeParams.sSurfaceInfo.ePixelFormat;
	  gDxeModeInfo.uNumPlanes                                     = sDisplayProp.sModeParams.sSurfaceInfo.uNumPlanes;
	  gDxeModeInfo.uBytesPerPixel                                 = sDisplayProp.sModeParams.sSurfaceInfo.uBytesPerPixel;
 
      // Setup the protocol information, set the current mode to an invalid mode forcing a set mode
      gDxeModeInfo.sProtocolInfo.MaxMode    = gDxeModeInfo.uNumModes[eDisplayId];
      gDxeModeInfo.sProtocolInfo.Mode       = (UINT32)-1;
      gDxeModeInfo.sProtocolInfo.SizeOfInfo = sizeof(EFI_GRAPHICS_OUTPUT_MODE_INFORMATION);
      gDxeModeInfo.sProtocolInfo.Info       = &gDxeModeInfo.sCurrentModeInfo;

      gDxeModeInfo.bExtSupported            = MDP_SUPPORTED_DISPLAY(MDP_DISPLAY_EXTERNAL);

      // Install display protocols only if panel is detected.
      // Make a new handle with EFI Graphics Protocol
      if (EFI_SUCCESS != (eStatus = gBS->InstallMultipleProtocolInterfaces (&hUEFIDisplayHandle,
                                                                            &gEfiDevicePathProtocolGuid,
                                                                            &DisplayDevicePath,
                                                                            &sOutputGUID,
                                                                            &gDisplayDxeOutputProtocol,
                                                                            &gQcomDisplayPwrCtrlProtocolGuid,
                                                                            &gDisplayPwrCtrlProtocolImplementation,
#ifndef FEATURE_XBOOT
                                                                            &gEfiDisplayPowerStateProtocolGuid,
                                                                            &gDisplayPwrProtocolImplementation,
#endif /*!FEATURE_XBOOT*/
                                                                            &gQcomDisplayUtilsProtocolGuid,
                                                                            &gQcomDisplayUtilsProtocolImplementation,
                                                                            &gEfiEdidActiveProtocolGuid,
                                                                            &gEdidActiveProtocol,
                                                                             NULL)))
      {
        DEBUG ((EFI_D_INFO, "DisplayDxe: InstallMultipleProtocolInterfaces failed!\n"));
      }
    } 
  }

  if (eStatus == EFI_SUCCESS)
  {
    if(EFI_SUCCESS != GetConfigValue ("EnableDisplayThread", &gDxeModeInfo.uMultiThreadded))
    {
      gDxeModeInfo.uMultiThreadded = 0;
    }

    // Spawn off thread to enable mode set if we are in a threadded environment
    if (gDxeModeInfo.uMultiThreadded )
    {
      if (EFI_UNSUPPORTED != (InitLock ("DispInit", &gDxeModeInfo.hModeLock)))
      {
        // If single CPU core is configured, the priority of this thread should be higher than UEFI dxe thread
        if (NULL != (gDxeModeInfo.hDispThread = ThreadCreate ("Disp", &SetModeThread, 0, UEFI_THREAD_PRIORITY + 1, DEFAULT_STACK_SIZE * 3)))
        {  
          if (MDP_STATUS_OK != MDP_SetMultiThreadState(TRUE))
          {
            DEBUG ((EFI_D_WARN, "DisplayDxe: Failed to set multiThread state to be enabled!\n"));    

            // Disable multi threadding
            gDxeModeInfo.uMultiThreadded = 0;
          }
          else
          {
            ThreadDetach (gDxeModeInfo.hDispThread);
            ThreadResume (gDxeModeInfo.hDispThread);
          }
        }
        else
        {
          // Disable multi threadding
          gDxeModeInfo.uMultiThreadded = 0;
        }
      }
      else
      {
        // Disable multi threadding
        gDxeModeInfo.uMultiThreadded = 0;
      }
    }
  }
  else
  {
    DEBUG((EFI_D_WARN, "DisplayDxe: Unregister Event Callbacks due to Error\n"));

    if (EFI_SUCCESS != gBS->CloseEvent(EfiExitBootServicesEvent))
    {
      DEBUG((EFI_D_ERROR, "DisplayDxe: Failed to Close event ExitBoot\n"));
    }

    DisplayDxeUnRegisterEvents();
  }

  MDP_LOG_FUNC_EXIT("DisplayDxeInitialize", 0x0);

  return eStatus;
}

#ifdef FEATURE_XBOOT
STATIC BOOLEAN g_LateInitialized = FALSE;
EFI_STATUS EFIAPI
LateInitialize(VOID)
{
  EFI_STATUS eStatus = EFI_SUCCESS;
  EFI_HANDLE DummyImageHandle = NULL;
  EFI_SYSTEM_TABLE *DummySystemTable = NULL;
  if (g_LateInitialized != FALSE) return eStatus;/*or EFI_ALREADY_STARTED*/
  eStatus = __DisplayDxeInitialize0(DummyImageHandle, DummySystemTable);
  if (eStatus != EFI_SUCCESS) return eStatus;
  eStatus = DisplayDxe_SetMode(&gDisplayDxeOutputProtocol, 0);
  if (eStatus != EFI_SUCCESS) return eStatus;
  g_LateInitialized = TRUE;
  return eStatus;
}
EFI_DISPLAY_X_LATE_INIT_PROTOCOL gDisplayXLateInit =
{
  DISPLAY_X_LATE_INIT_REVISION,
  LateInitialize,
};
EFI_GUID gDisplayXLateInitProtocolGuid = EFI_DISPLAYXLATEINIT_PROTOCOL_GUID;
EFI_STATUS EFIAPI
DisplayDxeInitialize /* XBOOT VERSION */
  (
  IN EFI_HANDLE         ImageHandle,
  IN EFI_SYSTEM_TABLE   *SystemTable
  )
{
  EFI_STATUS eStatus = EFI_SUCCESS;
  EFI_HANDLE Handle = NULL;
  EFI_HANDLE hUEFIDisplayHandle    = NULL;

 /* Do display subsystem initialization here */
  DisplaySubsystemInitialization();

  // Install display protocols only if panel is detected.
  // Make a new handle with EFI Graphics Protocol
  if (EFI_SUCCESS != (eStatus = gBS->InstallMultipleProtocolInterfaces (&hUEFIDisplayHandle,
                                                                        &gEfiDisplayPowerStateProtocolGuid,
                                                                        &gDisplayPwrProtocolImplementation,
                                                                        NULL)))
  {
    DEBUG ((EFI_D_INFO, "DisplayDxe: InstallMultipleProtocolInterfaces failed!\n"));
  }

  eStatus = gBS->InstallMultipleProtocolInterfaces(&Handle,
		&gDisplayXLateInitProtocolGuid,
		(VOID **)&gDisplayXLateInit,
		NULL);
  return EFI_SUCCESS;
}
#endif /* FEATURE_XBOOT */

/**
  Display DXE Protocol Query function
  
  @param  This             The EFI_GRAPHICS_OUTPUT_PROTOCOL instance.
  @param  ModeNumber       The mode number to return information on.
  @param  SizeOfInfo       A pointer to the size, in bytes, of the Info buffer.
  @param  Info             A pointer to callee allocated buffer that returns information about ModeNumber.

  @retval EFI_SUCCESS               Mode returned successfully
  @retval EFI_DEVICE_ERROR          Hardware error querying the mode
  @retval EFI_INVALID_PARAMETER     Invalid parameters/null parameters

**/
EFI_STATUS
DisplayDxe_QueryMode (
  EFI_GRAPHICS_OUTPUT_PROTOCOL          *This,
  UINT32                                ModeNumber,
  UINTN                                 *SizeOfInfo,
  EFI_GRAPHICS_OUTPUT_MODE_INFORMATION  **Info
  )
{
  EFI_STATUS                            eStatus   = EFI_SUCCESS;
  EFI_GRAPHICS_OUTPUT_MODE_INFORMATION *pModeInfo = NULL;

  MDP_LOG_FUNC_ENTRY_INFO("DisplayDxe_QueryMode", 0x0);

  if ((NULL == SizeOfInfo) || (NULL == Info) || (NULL == This))
  {
    eStatus = EFI_INVALID_PARAMETER;
  }
  else
  {
    MDP_Display_IDType eDisplayId = MDP_DISPLAY_PRIMARY;

    eDisplayId = GetFirstAvailableDisplayId();

    if (ModeNumber >= gDxeModeInfo.uNumModes[eDisplayId])
    {
      // Mode is out of range
      eStatus = EFI_INVALID_PARAMETER;
    }
    else if (NULL == (pModeInfo = AllocatePool(sizeof(EFI_GRAPHICS_OUTPUT_MODE_INFORMATION))))
    {
      // Allocation failed
      eStatus = EFI_INVALID_PARAMETER;
    }
    else
    {
      // Return results (single supported mode)
      MDP_OSAL_MEMCPY(pModeInfo, &gDxeModeInfo.aDxeModeList[eDisplayId][ModeNumber], sizeof(EFI_GRAPHICS_OUTPUT_MODE_INFORMATION));
       
      *Info       = pModeInfo;
      *SizeOfInfo = sizeof(EFI_GRAPHICS_OUTPUT_MODE_INFORMATION);
    }
  }

  MDP_LOG_FUNC_EXIT_INFO("DisplayDxe_QueryMode", 0x0);
   
  return eStatus;
}



/**
  Display DXE Protocol set mode
  
  @param  This                      The EFI_GRAPHICS_OUTPUT_PROTOCOL instance.
  @param  ModeNumber                Abstraction that defines the current video mode.

  @retval EFI_SUCCESS               The graphics mode specified by ModeNumber was selected.
  @retval EFI_DEVICE_ERROR          The device had an error and could not complete the request.
  @retval EFI_UNSUPPORTED           ModeNumber is not supported by this device.
  @retval EFI_OUT_OF_RESOURCES      Memory allocation failed
  @retval EFI_INVALID_PARAMETER     Invalid protocol handle passed in
**/
EFI_STATUS
DisplayDxe_SetMode (
  EFI_GRAPHICS_OUTPUT_PROTOCOL *This,
  UINT32                       ModeNumber
  )
{
  EFI_STATUS          eStatus                  = EFI_SUCCESS;
  MDP_Display_IDType  eDisplayId               = GetFirstAvailableDisplayId();
  MemRegionInfo       sMemRegionInfo;
  
  MDP_LOG_FUNC_ENTRY("DisplayDxe_SetMode", 0x0);

  if (NULL == This)
  {
    eStatus = EFI_INVALID_PARAMETER;
  }
  else if ((ModeNumber >= gDxeModeInfo.uNumModes[eDisplayId]) &&
           (FALSE      == Display_Utils_IsDisplayDisabled(eDisplayId)))
  {
    // If display is set to enabled state and ModeNumber check failed, then should return failure since there is no available mode.
    // However if display is set to disabled state, still need to pass panel string to kernel cmdline.
    eStatus = RETURN_UNSUPPORTED;
  }
  else if (TRUE == gDxeModeInfo.bModeSet)
  {
      // Enter this path if the mode has already been set once.  As all subsequent mode sets are virtual mode changes (scaled mode)
      if (ModeNumber != gDxeModeInfo.uModeId)
      {   
          EFI_GRAPHICS_OUTPUT_MODE_INFORMATION *pMode = &gDxeModeInfo.aDxeModeList[eDisplayId][ModeNumber];
          MDP_PropertiesParamType               sModeInfo;
          
          // Setup the virtual mode by changing the source cropping rectangle.
          MDP_OSAL_MEMZERO(&sModeInfo, sizeof(MDP_PropertiesParamType));
          sModeInfo.sModeParams.sRectInfo.uWidth  = pMode->HorizontalResolution;
          sModeInfo.sModeParams.sRectInfo.uHeight = pMode->VerticalResolution;
          
          if (MDP_STATUS_OK == MDPSetProperty(eDisplayId, MDP_DISPLAY_PROPERTY_SURFACE_RECT, &sModeInfo))
          {
            // Update the Dxe information there is an new mode configured
            MDP_OSAL_MEMCPY(&gDxeModeInfo.sCurrentModeInfo, pMode, sizeof(EFI_GRAPHICS_OUTPUT_MODE_INFORMATION));
  
            // Update both the internal and external mode number we report              
            gDxeModeInfo.uModeId                = ModeNumber;
            gDxeModeInfo.sProtocolInfo.Mode     = ModeNumber;
            eStatus                             = EFI_SUCCESS;            
          }
          else
          {
            DEBUG ((EFI_D_ERROR, "DisplayDxe: MDPSetMode() fail to change to a virtual mode!\n"));
            eStatus = EFI_DEVICE_ERROR;
          }
      
      }
      else
      {
        // This mode is already set, just continue
        eStatus = EFI_SUCCESS;
      }
  }
  else if (EFI_SUCCESS != (eStatus = GetMemRegionInfoByName("Display Reserved", &sMemRegionInfo)))
  {
    // Failed to get memory region info
    eStatus = EFI_DEVICE_ERROR;
  }
  else if (gDxeModeInfo.uMultiThreadded > 1)
  {
    // Mode set is already in progress, don't allow another call, but return success
    eStatus = EFI_SUCCESS;
  }
  else 
  {
    EFI_GRAPHICS_OUTPUT_MODE_INFORMATION *pMode            = &gDxeModeInfo.aDxeModeList[eDisplayId][ModeNumber];
    UINT32                                uBufferIndex     = 0;
    UINT32                                uNumDisplays     = 0;
    UINTN                                 uMemBase;
    UINTN                                 uMemSize;
    UINTN                                 uFrameBufferLength;
    FrameBufferOffsetType                 aFrameBuffers[FRAMEBUFFER_MAX_NUMBER];
    MDP_Status                            eMDPStatus[MDP_DISPLAY_MAX];
    MDP_PropertiesParamType               sDisplayProp;

    MDP_OSAL_MEMZERO(&eMDPStatus,       sizeof(eMDPStatus));
    MDP_OSAL_MEMZERO(&sDisplayProp,     sizeof(MDP_PropertiesParamType));
    MDP_OSAL_MEMZERO(&aFrameBuffers[0], sizeof(aFrameBuffers));

    if (gDxeModeInfo.uMultiThreadded)
    {
      // Hold the lock
      AcquireLock(gDxeModeInfo.hModeLock);

      // Increment to indicate we are processing the request
      gDxeModeInfo.uMultiThreadded++;
    }

    // Init the frame buffer info.
    uMemBase                            = (UINTN)sMemRegionInfo.MemBase;
    uMemSize                            = (UINTN)sMemRegionInfo.MemSize;
    uFrameBufferLength                  = (UINTN)pMode->HorizontalResolution * pMode->VerticalResolution * gDxeModeInfo.uNumPlanes * gDxeModeInfo.uBytesPerPixel;
    gDxeModeInfo.eDisplayFBAttrib       = sMemRegionInfo.CacheAttributes;

    for (eDisplayId = MDP_DISPLAY_PRIMARY; eDisplayId <= MDP_DISPLAY_EXTERNAL; eDisplayId++)
    {
      if ((FALSE == MDP_SUPPORTED_DISPLAY(eDisplayId)) ||
          (TRUE  == Display_Utils_IsDisplayDisabled(eDisplayId)))
      {
        // Display is not supported or set to disabled state, so skip MDPSetMode() function
        continue;
      }
      else if (FRAMEBUFFER_MAX_NUMBER == uNumDisplays)
      {
        // Break if uNumDisplays has been increased to FRAMEBUFFER_MAX_NUMBER.
        break;
      }
      else
      {
        EFI_GRAPHICS_OUTPUT_MODE_INFORMATION *pDisplayMode = &gDxeModeInfo.aDxeModeList[eDisplayId][ModeNumber];

        aFrameBuffers[uNumDisplays].uFrameWidth  = pDisplayMode->HorizontalResolution;
        aFrameBuffers[uNumDisplays].uFrameHeight = pDisplayMode->VerticalResolution * gDxeModeInfo.uNumPlanes;
	    aFrameBuffers[uNumDisplays].uStride      = pDisplayMode->HorizontalResolution * gDxeModeInfo.uBytesPerPixel;
        uNumDisplays ++;
      }
    }

    // Calculate frame buffer offsets based on uNumDisplays.
    CalculateFrameBufferOffsets(uMemBase, uMemSize, &aFrameBuffers[0], uNumDisplays);

    //////////////////////////
    // Allocate frame buffer//
    /////////////////////////
    /****************************************************************************************/

    // Clear the frame buffer
    MDP_OSAL_MEMZERO((VOID *)uMemBase, uMemSize);

    /* write through frame buffer */
    FlushStaleLines((VOID *)uMemBase, uMemSize);

    /****************************************************************************************/

    ////////////////////////////////////////////
    // Primary / Secondary / External Display //
    ////////////////////////////////////////////
    for (eDisplayId = MDP_DISPLAY_PRIMARY; eDisplayId <= MDP_DISPLAY_EXTERNAL; eDisplayId++)
    {
      if ((FALSE == MDP_SUPPORTED_DISPLAY(eDisplayId)) ||
          (TRUE  == Display_Utils_IsDisplayDisabled(eDisplayId)))
      {
        // Display is not supported or set to disabled state, so skip MDPSetMode() function
        continue;
      }
      else if (0 == gDxeModeInfo.uNumModes[eDisplayId])
      {
        continue;
      }
      else
      {
        EFI_GRAPHICS_OUTPUT_MODE_INFORMATION *pDisplayMode = &gDxeModeInfo.aDxeModeList[eDisplayId][ModeNumber];
        MDP_SetModeParamType                  sModeParams;

        MDP_OSAL_MEMZERO(&sModeParams, sizeof(MDP_SetModeParamType));
        
		// Setup the mode params
        sModeParams.sSurfaceInfo.ePixelFormat  = gDxeModeInfo.uFBPixelFormat ;
        sModeParams.sSurfaceInfo.uWidth        = pDisplayMode->HorizontalResolution;
        sModeParams.sSurfaceInfo.uHeight       = pDisplayMode->VerticalResolution;
        sModeParams.sSurfaceInfo.pPlane0Offset = aFrameBuffers[uBufferIndex].pFrameBufferStart;
        sModeParams.sSurfaceInfo.uPlane0Stride = pDisplayMode->HorizontalResolution * gDxeModeInfo.uBytesPerPixel;

        // Update the index to aFrameBuffers
        uBufferIndex++;
        if (uBufferIndex >= FRAMEBUFFER_MAX_NUMBER)
        {
          // Force to zero.
          uBufferIndex = 0;
        }

        //Set Mode index to selected Mode
        sModeParams.uModeIndex = gDxeModeInfo.uSelectedModeIndex[eDisplayId];

        if (MDP_STATUS_OK != (eMDPStatus[eDisplayId] = MDPSetMode(eDisplayId, &sModeParams, 0x0)))
        {
          DEBUG ((EFI_D_ERROR, "DisplayDxe: MDPSetMode() failed!\n"));
        }
      }
    }


    //
    // Setup the default backlight level
    //
    if (EFI_SUCCESS == GetChargerPowerStatus())
    {
      /* Assign the default brightness */
      sDisplayProp.uBacklightLevel = MDP_DISPLAY_DEFAULT_BRIGHTNESS;
    }
    else
    {
      // Charger power status is not okay or at off mode charging, so turn off backlight as default
      sDisplayProp.uBacklightLevel = 0;
      DEBUG ((EFI_D_ERROR, "DisplayDxe: Charger power status is not okay or at off mode charging, so turn off backlight!\n"));
    }

    for (eDisplayId = MDP_DISPLAY_PRIMARY; eDisplayId <= MDP_DISPLAY_EXTERNAL; eDisplayId++)
    {
      if ((TRUE  == MDP_SUPPORTED_DISPLAY(eDisplayId)) &&
          (TRUE  == Display_Utils_IsDisplayDisabled(eDisplayId)))
      {
        // Display is set to disabled state, only update display info to ABL
        Display_Utils_SetPanelConfiguration(eDisplayId);
        continue;
      }
      else if (0 == gDxeModeInfo.uNumModes[eDisplayId])
      {
        continue;
      }
      else if (MDP_STATUS_OK == eMDPStatus[eDisplayId])
      {
        MDPSetProperty(eDisplayId, MDP_DISPLAY_PROPERTY_BACKLIGHT, &sDisplayProp);

        //
        // Populate the display environment information, used to inform the OS driver of firmware state.
        //
        MDPSetProperty(eDisplayId, MDP_DISPLAY_PROPERTY_FIRMWAREENV, NULL);

        // Update ABL with selected panel info
        Display_Utils_SetPanelConfiguration(eDisplayId);
      }
    }


    // Save the current mode
    if ((EFI_SUCCESS == eStatus) && 
        (NULL != pMode))
    {
      MDP_OSAL_MEMCPY(&gDxeModeInfo.sCurrentModeInfo, pMode, sizeof(EFI_GRAPHICS_OUTPUT_MODE_INFORMATION));
      gDxeModeInfo.uModeId = ModeNumber;

      //
      // Set the protocol information
      //
      gDxeModeInfo.sProtocolInfo.FrameBufferBase  = (EFI_PHYSICAL_ADDRESS)aFrameBuffers[0].pFrameBufferStart;
      gDxeModeInfo.sProtocolInfo.FrameBufferSize  = aFrameBuffers[0].uFrameBufferLength;
      gDxeModeInfo.sProtocolInfo.Mode             = ModeNumber;
      gDxeModeInfo.sProtocolInfo.Info             = &gDxeModeInfo.sCurrentModeInfo;
      gDxeModeInfo.uDisplayFBWidth                = pMode->HorizontalResolution;
      gDxeModeInfo.uDisplayFBHeight               = pMode->VerticalResolution * gDxeModeInfo.uNumPlanes;
      gDxeModeInfo.bModeSet                       = TRUE;

      // Save frame buffer info.
      MDP_OSAL_MEMCPY(&gDxeModeInfo.aFrameBuffers[0], &aFrameBuffers[0], sizeof(aFrameBuffers));
    }

    // Done, release the lock and disable multi-threadding
    if (gDxeModeInfo.uMultiThreadded)
    {
      // Release the lock
      ReleaseLock(gDxeModeInfo.hModeLock);

      // Clear this flag so we can continue normal operation
      gDxeModeInfo.uMultiThreadded = 0;

      if (MDP_STATUS_OK != MDP_SetMultiThreadState(FALSE))
      {
        DEBUG ((EFI_D_WARN, "DisplayDxe: Failed to set multiThread state to be disabled!\n"));    
      }
    }
  }

  MDP_LOG_FUNC_EXIT("DisplayDxe_SetMode", 0x0);

  return eStatus;
}

/**
  Display DXE Protocol set mode for external display
  
  @param  DisplayId                 display id, can be either primary, secondary or external
  @param  ModeNumber                Abstraction that defines the current video mode.
  @param  Flags                     Other info

  @retval EFI_SUCCESS               The graphics mode specified by ModeNumber was selected.
  @retval EFI_DEVICE_ERROR          The device had an error and could not complete the request.
  @retval EFI_UNSUPPORTED           ModeNumber is not supported by this device.
  @retval EFI_OUT_OF_RESOURCES      Memory allocation failed
  @retval EFI_INVALID_PARAMETER     Invalid protocol handle passed in
**/
EFI_STATUS
DisplayDxe_SetModeExt (
  UINT32                       DisplayId,
  UINT32                       ModeNumber,
  UINT32                       Flags
)
{
    MDP_PowerParamsType                  sPowerParams;
    MDP_DetectParamType                  sDetectParams;
    MDP_PropertiesParamType              sDisplayProp;
    MDP_SetModeParamType                 sModeParams;
    VOID                                 *pFrameBufferBase = (VOID *)gDxeModeInfo.sProtocolInfo.FrameBufferBase;
    EFI_STATUS                           eStatus = EFI_SUCCESS;

    MDP_LOG_FUNC_ENTRY("DisplayDxe_SetModeExt", DisplayId);
    
    if (FALSE == gDxeModeInfo.bExtSupported)
    {
      eStatus = EFI_UNSUPPORTED;
    }
    else if (MDP_DISPLAY_EXTERNAL == DisplayId)
    {
      EFI_GRAPHICS_OUTPUT_MODE_INFORMATION *pMode = &gDxeModeInfo.aDxeModeList[MDP_DISPLAY_PRIMARY][0]; /* primary display with mode 0 */

      if ((pMode->HorizontalResolution > 0) &&      /* primary display had presented */
          (pMode->VerticalResolution > 0))
      {
           //////////////////////
           // External Display //
           //////////////////////
         if (gDxeModeInfo.uNumModes[MDP_DISPLAY_EXTERNAL] == 0) /* only allow SetModeExt once */
         {
            MDP_OSAL_MEMZERO(&sPowerParams, sizeof(MDP_PowerParamsType));
            sPowerParams.bPowerOn = TRUE;
            sDisplayProp.bDisplayPwrState = TRUE;

            if (MDP_STATUS_OK != MDPPower(MDP_DISPLAY_EXTERNAL, &sPowerParams, 0x0))
            {
                DEBUG ((EFI_D_ERROR, "DisplayDxe: External panel power up failed!\n"));    
            }              
            else 
            {
                MDP_OSAL_MEMZERO(&sDetectParams, sizeof(MDP_DetectParamType));
                      
                // Default reporting of External display
                if ((MDP_STATUS_OK != MDPDetect(MDP_DISPLAY_EXTERNAL, &sDetectParams, Flags)) || 
                    (FALSE == sDetectParams.bDisplayDetected))
                {
                    // External display not detected, turn off and continue on
                    DEBUG ((EFI_D_ERROR, "DisplayDxe: External panel not detected\n"));    
                    eStatus = EFI_NOT_FOUND; 
                }
                else
                {
                     sDetectParams.uModeSelected = ModeNumber; /* which mode to display */
                     if (MDP_STATUS_OK != (eStatus = DisplayDxeSetMode(MDP_DISPLAY_EXTERNAL,&sDetectParams, Flags)))
                     {
                        DEBUG ((EFI_D_ERROR, "DisplayDxe: failed to select external display mode!\n"));
                     }
                     else if (MDP_STATUS_OK != (eStatus = MDPSetProperty(MDP_DISPLAY_EXTERNAL, MDP_DISPLAY_PROPERTY_POWER_STATE, &sDisplayProp)))
                     {
                        DEBUG ((EFI_D_ERROR, "DisplayDxe: failed to set external display power state to on!\n"));
                     }
                     else
                     {
                       // Setup the mode params
                       MDP_OSAL_MEMZERO(&sModeParams, sizeof(MDP_SetModeParamType));
                       sModeParams.sSurfaceInfo.ePixelFormat  = gDxeModeInfo.uFBPixelFormat ;
                       sModeParams.sSurfaceInfo.uWidth        = pMode->HorizontalResolution;
                       sModeParams.sSurfaceInfo.uHeight       = pMode->VerticalResolution;
                       sModeParams.sSurfaceInfo.pPlane0Offset = pFrameBufferBase;
                       sModeParams.sSurfaceInfo.uPlane0Stride = pMode->HorizontalResolution * gDxeModeInfo.uBytesPerPixel;

                       //Set Mode index to selected Mode
                       sModeParams.uModeIndex                 = gDxeModeInfo.uSelectedModeIndex[MDP_DISPLAY_EXTERNAL];
           
                       // Setup the mode
                       if (MDP_STATUS_OK != MDPSetMode(MDP_DISPLAY_EXTERNAL, &sModeParams, 0x0))
                       {
                          DEBUG ((EFI_D_ERROR, "DisplayDxe: MDPSetModeExt() failed!\n"));
                          eStatus = EFI_DEVICE_ERROR;
                       }
                     }
                 }
            }
         }
       }
       else 
       {
          eStatus = EFI_DEVICE_ERROR;
          DEBUG ((EFI_D_ERROR, "DisplayDxe: Cannot change modes on the external if the primary has not been set yet\n"));
       }
   }
   else
   {
      eStatus = EFI_DEVICE_ERROR;
   }

  MDP_LOG_FUNC_EXIT("DisplayDxe_SetModeExt", DisplayId);

  return eStatus;
}


/**
  Display DXE Protocol Blt function
  
  @param  This         Protocol instance pointer.
  @param  eDisplayId   Display ID.
  @param  BltBuffer    Buffer containing data to blit into video buffer. This
                       buffer has a size of Width*Height*sizeof(EFI_GRAPHICS_OUTPUT_BLT_PIXEL)
  @param  BltOperation Operation to perform on BlitBuffer and video memory
  @param  SourceX      X coordinate of source for the BltBuffer.
  @param  SourceY      Y coordinate of source for the BltBuffer.
  @param  DestinationX X coordinate of destination for the BltBuffer.
  @param  DestinationY Y coordinate of destination for the BltBuffer.
  @param  Width        Width of rectangle in BltBuffer in pixels.
  @param  Height       Hight of rectangle in BltBuffer in pixels.
  @param  Delta        OPTIONAL

  @retval EFI_SUCCESS           The Blt operation completed.
  @retval EFI_INVALID_PARAMETER BltOperation is not valid or source/destination parameters are invalid
  @retval EFI_DEVICE_ERROR      A hardware error occured writting to the video buffer.


**/
EFI_STATUS
DisplayDxe_Blt (
  IN  EFI_GRAPHICS_OUTPUT_PROTOCOL            *This,
  IN  MDP_Display_IDType                      eDisplayId,
  IN  EFI_GRAPHICS_OUTPUT_BLT_PIXEL           *BltBuffer,
  IN  EFI_GRAPHICS_OUTPUT_BLT_OPERATION       BltOperation,
  IN  UINTN                                   SourceX,
  IN  UINTN                                   SourceY,
  IN  UINTN                                   DestinationX,
  IN  UINTN                                   DestinationY,
  IN  UINTN                                   Width,
  IN  UINTN                                   Height,
  IN  UINTN                                   Delta)
{
    EFI_STATUS        eStatus = EFI_SUCCESS;

    MDP_LOG_FUNC_ENTRY_INFO("DisplayDxe_Blt", 0x0);

    if (NULL == This)
    {
        eStatus = EFI_INVALID_PARAMETER;
    }
    else if (FALSE == gDxeModeInfo.bModeSet)
    {
         eStatus = EFI_NOT_STARTED;
    }
    else
    {
      FrameBufferOffsetType  sFrameBuffer;

      MDP_OSAL_MEMZERO(&sFrameBuffer, sizeof(FrameBufferOffsetType)); 

      if (EFI_SUCCESS != GetFrameBufferInfo(eDisplayId, &sFrameBuffer))
      {
        sFrameBuffer.pFrameBufferStart = (UINT64 *)gDxeModeInfo.sProtocolInfo.FrameBufferBase;
        sFrameBuffer.uFrameWidth       = gDxeModeInfo.sCurrentModeInfo.HorizontalResolution;
        sFrameBuffer.uFrameHeight      = gDxeModeInfo.sCurrentModeInfo.VerticalResolution * gDxeModeInfo.uNumPlanes;
        sFrameBuffer.uStride           = gDxeModeInfo.sCurrentModeInfo.HorizontalResolution * gDxeModeInfo.uBytesPerPixel;
      } 
	    
      switch (BltOperation)
      {
      case EfiBltBufferToVideo:
        {
          UINT8 *pSrcBuffer = (UINT8*)BltBuffer;
          UINT8 *pDstBuffer = (UINT8*)sFrameBuffer.pFrameBufferStart;
          UINTN SrcStride, DstStride, CopyWidth, CopyHeight;

          if ((DestinationX >= sFrameBuffer.uFrameWidth) ||
              (DestinationY >= sFrameBuffer.uFrameHeight))
          {
            // Do nothing here if destination position is out of range.
            eStatus = EFI_SUCCESS;
          }
          else
          {
            if ((DestinationX + Width) > sFrameBuffer.uFrameWidth)
            {
              CopyWidth  = sFrameBuffer.uFrameWidth - DestinationX;
            }
            else
            {
              CopyWidth  = Width;
            }

            if ((DestinationY + Height) > sFrameBuffer.uFrameHeight)
            {
              CopyHeight = sFrameBuffer.uFrameHeight - DestinationY;
            }
            else
            {
              CopyHeight = Height;
            }

            /* Video buffer stride in bytes, consider padding as well */
            DstStride = sFrameBuffer.uStride;

            /* Src buffer stride in bytes. Delta is valid when X or Y is not 0 */
            SrcStride = Width * DISPLAYDXE_DEFAULT_BYTES_PER_PIXEL;
            if (Delta != 0)
            {  
              SrcStride = Delta;
            }

			DisplayDxeBlt (pSrcBuffer,
						   pDstBuffer,
						   SourceX, 
						   SourceY, 
						   CopyWidth, 
						   CopyHeight,
						   SrcStride,
						   DestinationX,
						   DestinationY,
						   sFrameBuffer.uFrameWidth,
						   sFrameBuffer.uFrameHeight,
						   DstStride,
						   DISPLAYDXE_DEFAULT_BYTES_PER_PIXEL,
						   gDxeModeInfo.uFBPixelFormat);
						 
             /* If display frame buffer is cached, need to call cache maintenance function */
            FlushStaleLines(((UINT8*)pDstBuffer) + (DstStride * DestinationY), (DstStride * CopyHeight));

            eStatus = EFI_SUCCESS;
          }
        }
        break;

      case EfiBltVideoToBltBuffer:
        {  
          UINT8 *pDstBuffer = (UINT8*)BltBuffer;
          UINT8 *pSrcBuffer = (UINT8*)sFrameBuffer.pFrameBufferStart;
          UINTN SrcStride, DstStride, CopyWidth, CopyHeight;

          if (((SourceX + Width) > sFrameBuffer.uFrameWidth) ||
              ((SourceY + Height) > sFrameBuffer.uFrameHeight))
          {
            return EFI_INVALID_PARAMETER;
          }

          CopyWidth  = Width;
          CopyHeight = Height;

          /* Video buffer stride in bytes, consider padding as well */
          SrcStride = sFrameBuffer.uStride;

          /* Buffer stride in bytes. Delta is valid when X or Y is not 0 */
          DstStride = sFrameBuffer.uStride;
          if (Delta != 0)
          {
            DstStride = Delta;
          }

          DisplayDxeBltInternal (pSrcBuffer,
                                 pDstBuffer,
                                 SourceX, 
                                 SourceY, 
                                 CopyWidth, 
                                 CopyHeight,
                                 SrcStride,
                                 DestinationX,
                                 DestinationY,
                                 DstStride,
                                 DISPLAYDXE_DEFAULT_BYTES_PER_PIXEL);

          eStatus = EFI_SUCCESS;
        }
        break; 

      case EfiBltVideoFill:
        {
          UINT32 SrcPixel = *(UINT32*)BltBuffer;
          UINTN  DstStride, CopyWidth, CopyHeight;
          UINT32 x,y;

          if ((DestinationX >= sFrameBuffer.uFrameWidth) ||
              (DestinationY >= sFrameBuffer.uFrameHeight))
          {
            // Do nothing here if destination position is out of range.
            eStatus = EFI_SUCCESS;
          }
          else
          {
            if ((DestinationX + Width)  > sFrameBuffer.uFrameWidth)
            {
              CopyWidth  = sFrameBuffer.uFrameWidth - DestinationX;
            }
            else
            {
              CopyWidth  = Width;
            }

            if ((DestinationY + Height) > sFrameBuffer.uFrameHeight)
            {
              CopyHeight = sFrameBuffer.uFrameHeight - DestinationY;
            }
            else
            {
              CopyHeight = Height * gDxeModeInfo.uNumPlanes;
            }

            /* Video buffer stride in bytes, consider padding as well */
            DstStride = sFrameBuffer.uStride;

            // If just clearing the whole screen, do it efficiently
            if ((0      == DestinationX)                             &&
                (0      == DestinationY)                             &&
                (Width  == sFrameBuffer.uFrameWidth)   &&
                (Height == sFrameBuffer.uFrameHeight))
            {
              UINT64 *pDstBuffer  = (UINT64*)sFrameBuffer.pFrameBufferStart;
              UINT32  uIterations = (CopyHeight * CopyWidth) / 8;  // Each iteration is 8 DWords
              UINT64  PxlVal      = SrcPixel;

              PxlVal = (PxlVal << 32) | SrcPixel;

              for (y = 0; y < uIterations; y++)
              {
                pDstBuffer[4 * y]     = PxlVal;
                pDstBuffer[4 * y + 1] = PxlVal;
                pDstBuffer[4 * y + 2] = PxlVal;
                pDstBuffer[4 * y + 3] = PxlVal;
              }

              FlushStaleLines((UINT8*)pDstBuffer, (CopyHeight * CopyWidth));
            }
            else
            {
              UINT32 *pDstBuffer = (UINT32*)sFrameBuffer.pFrameBufferStart;

              /* Adjust Destination location */
              pDstBuffer = (UINT32*)(((UINT8*)pDstBuffer) + (DestinationY * DstStride) + DestinationX * DISPLAYDXE_DEFAULT_BYTES_PER_PIXEL); 

              /* Do the actual blitting */
              for (y = 0; y < CopyHeight; y++)
              {
                for (x = 0; x < CopyWidth; x++)
                {
                  pDstBuffer[x] = SrcPixel;
                }
                /* Increment by stride number of bytes */
                pDstBuffer = (UINT32*)((UINT8*)pDstBuffer + DstStride);
              }

              /* If display frame buffer is cached, need to call cache maintenance function */
              pDstBuffer = (UINT32*)sFrameBuffer.pFrameBufferStart;
              FlushStaleLines(((UINT8*)pDstBuffer) + (DstStride * DestinationY), (DstStride * CopyHeight));
            }

            eStatus = EFI_SUCCESS;
           }
        }
        break;

      case EfiBltVideoToVideo:
        {
          UINT8 *pSrcBuffer = (UINT8*)sFrameBuffer.pFrameBufferStart;
          UINT8 *pDstBuffer = (UINT8*)sFrameBuffer.pFrameBufferStart;
          UINTN  Stride, CopyWidth, CopyHeight;

          if (((SourceX + Width) > sFrameBuffer.uFrameWidth))
            Width = sFrameBuffer.uFrameWidth - SourceX;

          if (((SourceY + Height) > sFrameBuffer.uFrameHeight))
            Height = sFrameBuffer.uFrameHeight - SourceY;

          if (((DestinationX + Width) > sFrameBuffer.uFrameWidth))
            Width = sFrameBuffer.uFrameWidth - DestinationX;

          if (((DestinationY + Height) > sFrameBuffer.uFrameHeight))
            Height = sFrameBuffer.uFrameHeight - DestinationY;

          CopyWidth  = Width;
          CopyHeight = Height;

          /* Video buffer stride in bytes, consider padding as well */
          Stride = sFrameBuffer.uStride;

          DisplayDxeBltInternal (pSrcBuffer,
                                 pDstBuffer,
                                 SourceX, 
                                 SourceY, 
                                 CopyWidth, 
                                 CopyHeight,
                                 Stride,
                                 DestinationX,
                                 DestinationY,
                                 Stride,
                                 DISPLAYDXE_DEFAULT_BYTES_PER_PIXEL);

          /* If display frame buffer is cached, need to call cache maintenance function */
          FlushStaleLines(((UINT8*)pDstBuffer) + (Stride * DestinationY), (Stride * CopyHeight));
          eStatus = EFI_SUCCESS;

        }
        break;

      default:
        DEBUG ((EFI_D_INFO, "DisplayDxe: BltOperation not supported\n"));
        eStatus = RETURN_INVALID_PARAMETER;
        break;
      }    
    }


    return eStatus;    
}


/**
  Display DXE Protocol Blt Legacy function
  
  @param  This         Protocol instance pointer.
  @param  BltBuffer    Buffer containing data to blit into video buffer. This
                       buffer has a size of Width*Height*sizeof(EFI_GRAPHICS_OUTPUT_BLT_PIXEL)
  @param  BltOperation Operation to perform on BlitBuffer and video memory
  @param  SourceX      X coordinate of source for the BltBuffer.
  @param  SourceY      Y coordinate of source for the BltBuffer.
  @param  DestinationX X coordinate of destination for the BltBuffer.
  @param  DestinationY Y coordinate of destination for the BltBuffer.
  @param  Width        Width of rectangle in BltBuffer in pixels.
  @param  Height       Hight of rectangle in BltBuffer in pixels.
  @param  Delta        OPTIONAL

  @retval EFI_SUCCESS           The Blt operation completed.
  @retval EFI_INVALID_PARAMETER BltOperation is not valid or source/destination parameters are invalid
  @retval EFI_DEVICE_ERROR      A hardware error occured writting to the video buffer.


**/
static EFI_STATUS
DisplayDxe_Blt_Legacy (
  IN  EFI_GRAPHICS_OUTPUT_PROTOCOL            *This,
  IN  EFI_GRAPHICS_OUTPUT_BLT_PIXEL           *BltBuffer,
  IN  EFI_GRAPHICS_OUTPUT_BLT_OPERATION       BltOperation,
  IN  UINTN                                   SourceX,
  IN  UINTN                                   SourceY,
  IN  UINTN                                   DestinationX,
  IN  UINTN                                   DestinationY,
  IN  UINTN                                   Width,
  IN  UINTN                                   Height,
  IN  UINTN                                   Delta)
{
  EFI_STATUS          eStatus    = EFI_SUCCESS;
  MDP_Display_IDType  eDisplayId = MDP_DISPLAY_PRIMARY;

  eStatus = DisplayDxe_Blt(This, eDisplayId, BltBuffer, BltOperation, SourceX, SourceY, DestinationX, DestinationY, Width, Height, Delta);

  return eStatus;
}


/**********************************************************************************************************************
     Local Functions
**/


/**
  ClampResolution
  
  Clamps a resolution to a specific limit.  Handles cases where input & clamp are in different orientation (porait vs landscape)
    
  @param  uSourceWidth          Source width
  @param  uSourceHeight         Source height
  @param  uClampWidth           Clamp width
  @param  uClampHeight          Clamp height
 
@retval MDP_ResolutionType      Clamped resolution

**/
static MDP_ResolutionType ClampResolution(UINT32 uSourceWidth, UINT32 uSourceHeight, UINT32 uClampWidth, UINT32 uClampHeight)
{
    MDP_ResolutionType sResult;
    
    // Default is to return the input source width and height
    sResult.uWidth  = uSourceWidth;
    sResult.uHeight = uSourceHeight;    
       
    // Limit by total number of pixels
    if ((uSourceWidth * uSourceHeight) > (uClampWidth * uClampHeight)) 
    {
       if (uSourceHeight > uSourceWidth)
       {
         // Portrait mode panel, clamp to height x width
         sResult.uHeight = uClampWidth;  
         sResult.uWidth  = uClampHeight;
       }
       else
       {
         // Landscape mode panel, clamp to width x height
         sResult.uWidth  = uClampWidth;  
         sResult.uHeight = uClampHeight;
       }
    }

    MDP_LOG_FUNC_EXIT_INFO("DisplayDxe_Blt", 0x0);
    
    return sResult;
}


/**
  DisplayDxeSetMode
  
  Display DXE Local function to select the mode out of supported modes. Function will also generate a list of
  virtual modes for the internal display.
  
  @param  eDisplayId        Display ID
  @param  pDisplayModes     List of modes reported by the sink 
  @param  uFlags            Mode flags 
  
  @retval EFI_SUCCESS       Execution successful
  @retval other             Error occurred

**/

static EFI_STATUS DisplayDxeSetMode(MDP_Display_IDType eDisplayId, MDP_DetectParamType  *pDisplayModes, uint32 uFlags)
{
   EFI_STATUS     Status = EFI_SUCCESS;

   if (NULL == pDisplayModes)
   {
      Status = EFI_INVALID_PARAMETER;
   }
   else if (0 == pDisplayModes->uSupportedModes)
   {
      Status = EFI_NOT_FOUND;
   }
   else
   {
      MDP_PropertiesParamType sDisplayProp;
      
      // Handle each display
      switch (eDisplayId)
      {
        //For Primary always default to the first mode which is native.
        case MDP_DISPLAY_PRIMARY:
        case MDP_DISPLAY_SECONDARY:
        {
          // Store the mode that the caller requested   
          gDxeModeInfo.uSelectedModeIndex[eDisplayId] = pDisplayModes->uModeSelected;

          // Internal displays are limited to select only the physical resolution (index 0)
          MDP_OSAL_MEMZERO(&sDisplayProp, sizeof(MDP_PropertiesParamType)); 
          sDisplayProp.sModeParams.uModeIndex = 0;   

          // Notify the driver that we have selected a particular mode
          if (MDP_STATUS_OK != MDPSetProperty(eDisplayId, MDP_DISPLAY_PROPERTY_MODE_INFO, &sDisplayProp))
          {
            DEBUG((EFI_D_ERROR, "DisplayDxe: Failed to set property while forcing mode\n"));
          }
        }
        break;

        // Select the best mode out of the list of supported modes available on the external monitor
        case MDP_DISPLAY_EXTERNAL:
        {
           // Store the mode that the caller requested
           gDxeModeInfo.uSelectedModeIndex[eDisplayId] = pDisplayModes->uModeSelected;            
           
           // The FORCE_MODE flag forces a specific resolution from the drivers table, irrespetive of wha the EDID reports.
           if (uFlags & DISPLAY_UTILS_EXT_FORCE_MODE)
           {
               // Use MDP_DISPLAY_PROPERTY_SELECT_MODE_INDEX property to select a specific mode
               MDP_OSAL_MEMZERO(&sDisplayProp, sizeof(MDP_PropertiesParamType)); 
               sDisplayProp.uIndex = pDisplayModes->uModeSelected;
               
               if (MDP_STATUS_OK == MDPSetProperty(eDisplayId, MDP_DISPLAY_PROPERTY_SELECT_MODE_INDEX,  &sDisplayProp))
               {
                 // Mode is from the drvier, resolution is not available so we can only print the index
                 DEBUG ((EFI_D_ERROR, "DisplayDxe: External Mode#%d selected.\n",
                             pDisplayModes->uModeSelected));
               
               }
               else
               {
                  DEBUG((EFI_D_ERROR, "DisplayDxe: Failed to set property while forcing mode\n"));
                  Status = RETURN_INVALID_PARAMETER;                   
               }            
           }
           else
           {
               // Use MDP_DISPLAY_PROPERTY_MODE_INFO property to select a specific mode            
               MDP_OSAL_MEMZERO(&sDisplayProp, sizeof(MDP_PropertiesParamType)); 
               sDisplayProp.sModeParams.uModeIndex = gDxeModeInfo.uSelectedModeIndex[eDisplayId];               

               // Notify the driver that we have selected a particular mode
               if (MDP_STATUS_OK == MDPSetProperty(eDisplayId, MDP_DISPLAY_PROPERTY_MODE_INFO, &sDisplayProp))
               {
                  uint32 uModeID = gDxeModeInfo.uSelectedModeIndex[eDisplayId];
                  
                  DEBUG ((EFI_D_ERROR, "DisplayDxe: External Panel Mode#%d %dx%d %dHz selected.\n",
                          uModeID,
                          pDisplayModes->aModeList[uModeID].uWidth,
                          pDisplayModes->aModeList[uModeID].uHeight,
                         (pDisplayModes->aModeList[uModeID].uRefreshRate / 0x10000)));
               }
               else
               {
                 DEBUG((EFI_D_ERROR, "DisplayDxe: Failed to set property while forcing mode\n"));
                 Status = RETURN_INVALID_PARAMETER;
               }
           }
        }                      
        break;

        default:
            Status = EFI_INVALID_PARAMETER;
        break;
      }

      // If we haven't built the mode table for this display, build it now
      if ((EFI_SUCCESS == Status) &&
          (0 == gDxeModeInfo.uNumModes[eDisplayId]))
      {
         // Mode set on the display is the native panel resolution, which can be different from what the Dxe reports.
        UINT32                  uPhysicalResolution = gDxeModeInfo.uSelectedModeIndex[eDisplayId];
        UINT32                  uResLimitIndex      = (PcdGet32(PcdFrameBufMaxRes) < DISPLAY_TABLE_SIZE(gFBResLimit))?PcdGet32(PcdFrameBufMaxRes):0;
        UINT32                  uModeIndex          = 0;
        UINT32                  uVirtualModeIndex   = 0;
        
        while (uModeIndex < DISPLAYDXE_MAX_MODES)
        {
          MDP_ResolutionType                    sResolution;
          EFI_GRAPHICS_OUTPUT_MODE_INFORMATION *pMode = &gDxeModeInfo.aDxeModeList[eDisplayId][uModeIndex];
        
          // Mode 0 is a special case where the resolution comes from the panel native resolution, all other modes are virtual.
          if (0 == uModeIndex)
          {
               sResolution.uWidth  = pDisplayModes->aModeList[uPhysicalResolution].uWidth;
               sResolution.uHeight = pDisplayModes->aModeList[uPhysicalResolution].uHeight;
          }
		  else if (TRUE == PcdGetBool(PcdVirtualResDisable))
		  { 
			/* Skip virtual resolutions/mode if PcdVirtualResDisable is set to true so that native resolution is used. */
			break;  
		  }
          else if ((MDP_DISPLAY_PRIMARY == eDisplayId) &&
                   (uVirtualModeIndex < DISPLAY_TABLE_SIZE(gVirtualResTable)))
          {
               // Virtual resolutions are only applicable to the primary               
               // Add virtual resolutions from hardcoded gVirtualResTable (table is in portait.  Switch if the panel is landscape)
               if (pDisplayModes->aModeList[uPhysicalResolution].uWidth >= pDisplayModes->aModeList[uPhysicalResolution].uHeight)
               {
                 sResolution.uWidth  = gVirtualResTable[uVirtualModeIndex].uWidth;
                 sResolution.uHeight = gVirtualResTable[uVirtualModeIndex].uHeight;
               }
               else
               {
                 sResolution.uWidth  = gVirtualResTable[uVirtualModeIndex].uHeight;
                 sResolution.uHeight = gVirtualResTable[uVirtualModeIndex].uWidth;
               }
        
               // Clamp to ensure virtual resolution is not larger than native, required because only upscaled modes are supported.
               sResolution = ClampResolution(sResolution.uWidth, 
                                             sResolution.uHeight, 
                                             pDisplayModes->aModeList[uPhysicalResolution].uWidth, 
                                             pDisplayModes->aModeList[uPhysicalResolution].uHeight);
               
               uVirtualModeIndex++;
          }
          else
          {
             // No more resolutions or virtual resolutions to add
             break;
          }
        
          // Populate standard fields that are not resolution dependent
          pMode->Version                              = GRAPHICS_OUTPUT_PROTOCOL_REVISION;
          pMode->PixelFormat                          = DISPLAYDXE_DEFAULT_PIXEL_FORMAT;
          pMode->PixelInformation.RedMask             = DISPLAYDXE_RED_MASK;
          pMode->PixelInformation.GreenMask           = DISPLAYDXE_GREEN_MASK;
          pMode->PixelInformation.BlueMask            = DISPLAYDXE_BLUE_MASK;
          pMode->PixelInformation.ReservedMask        = DISPLAYDXE_ALPHA_MASK;
        
          // Ensure we clamp the resolution to not exceed the limits set by the resolution limit PCD
          // Note: After clamping we don't check if the same resolution is in the list already.
          sResolution = ClampResolution(sResolution.uWidth, sResolution.uHeight, gFBResLimit[uResLimitIndex].uWidth, gFBResLimit[uResLimitIndex].uHeight);
          
          pMode->HorizontalResolution                 = sResolution.uWidth;
          pMode->VerticalResolution                   = sResolution.uHeight;
          pMode->PixelsPerScanLine                    = pMode->HorizontalResolution;
          gDxeModeInfo.uNumModes[eDisplayId]++;
          uModeIndex++;
        }
      }
   }
   return Status;
}


/**
  Display DXE Internal Blit function
  
  @param  pSrc              Pointer (non NULL) to source buffer.
  @param  pdst              Pointer (non NULL) to destination buffer.                        

  @param  uSrcX             X coordinate of source.
  @param  uSrcY             Y coordinate of source.
  @param  uSrcWidth         Width of source rectangle in pixels.
  @param  uSrcHeight        Height of source rectangle in pixels.
  @param  uSrcStride        Stride of source rectangle in bytes.
  
  @param  uDstX             X coordinate of destination.
  @param  uDstY             Y coordinate of destination.
  @param  uDstStride        Stride of destination rectangle in bytes.

  @param  uBytesPerPixel    Number of bytes per pixel. 
**/

static void DisplayDxeBltInternal (
  UINT8   *pSrc,
  UINT8   *pDst,
  UINTN    uSrcX,
  UINTN    uSrcY,
  UINTN    uSrcWidth,
  UINTN    uSrcHeight,
  UINTN    uSrcStride,
  UINTN    uDstX,
  UINTN    uDstY,
  UINTN    uDstStride,
  UINTN    uBytesPerPixel
  )
{
  UINT32 uI = 0;
  UINT32 uSrcWidthBytes = uSrcWidth * uBytesPerPixel;  
  
  /* move src pointer to start of src rectangle */
  pSrc += (uSrcY * uSrcStride) + (uSrcX * uBytesPerPixel);

  /* move dest pointer to start of dest rectangle */
  pDst += (uDstY * uDstStride) + (uDstX * uBytesPerPixel); 

  /* Blit Operation 
   *
   *  We use MDP_OSAL_MEMCPY which invokes Neon memcpy (kr_memcpy.asm) 
   *  This memcpy supports overlapped src and dst buffers but copying may not be optimal in the overlap case 
   */  
  for (uI = 0; uI < uSrcHeight; ++uI)
  {
    MDP_OSAL_MEMCPY((void*)pDst, (void*)pSrc, uSrcWidthBytes);

    pDst += uDstStride;
    pSrc += uSrcStride;
  }
}

/**
  Display DXE Internal Blit function for Planar formats
  
  @param  pSrc              Pointer (non NULL) to source buffer.
  @param  pdst              Pointer (non NULL) to destination buffer.                        

  @param  uSrcX             X coordinate of source.
  @param  uSrcY             Y coordinate of source.
  @param  uSrcWidth         Width of source rectangle in pixels.
  @param  uSrcHeight        Height of source rectangle in pixels.
  @param  uSrcStride        Stride of source rectangle in bytes.
  
  @param  uDstX             X coordinate of destination.
  @param  uDstY             Y coordinate of destination.
  @param  uDstWidth         Width of dest rectangle in pixels
  @param  uDstHeight        Height of dest rectangle in pixels
  @param  uDstStride        Stride of destination rectangle in bytes.

  @param  uBytesPerPixel    Number of bytes per pixel. 
**/
static void DisplayDxeBltInternalPlanar (
  UINT8   *pSrc,
  UINT8   *pDst,
  UINTN    uSrcX,
  UINTN    uSrcY,
  UINTN    uSrcWidth,
  UINTN    uSrcHeight,
  UINTN    uSrcStride,
  UINTN    uDstX,
  UINTN    uDstY,
  UINTN    uDstWidth,
  UINTN    uDstHeight,
  UINTN    uDstStride,
  UINTN    uBytesPerPixel
  )
{
  static uint8  uRGBBuffer[3 * FRAMEBUFFER_MAX_WIDTH];
  UINT8  *pRed;
  UINT8  *pGreen;
  UINT8  *pBlue;
  UINT32 uI                                 = 0;
  UINTN  uGreenDstStride                    = (uDstHeight / 3) * uDstStride;
  UINTN  uBlueDstStride                     = (2 * uDstHeight / 3) * uDstStride;
  UINTN  uNumPixelPerPlanarRow              = uSrcStride / uBytesPerPixel;

  /* check if max framebuffer width is greater than current fb width */
  if (uSrcWidth < FRAMEBUFFER_MAX_WIDTH)
  {
	pRed   = uRGBBuffer;
	pGreen = (uRGBBuffer + uSrcWidth);
	pBlue  = (uRGBBuffer + 2 * uSrcWidth);

	/* move src pointer to start of src rectangle */
    pSrc += (uSrcY * uSrcStride) + (uSrcX * uBytesPerPixel);

    /* move dest pointer to start of dest rectangle */
    pDst += (uDstY * uDstStride) + (uDstX * uBytesPerPixel);

    /* Blit Operation
     *
     *  We use MDP_OSAL_MEMCPY which invokes Neon memcpy (kr_memcpy.asm)
     *  This memcpy supports overlapped src and dst buffers but copying may not be optimal in the overlap case
     */
    for (uI = 0; uI < uSrcHeight; ++uI)
    {
	  for (UINTN j = 0,i = 0; i < uSrcStride; i += uBytesPerPixel)
	  {
	    pRed[j]   = pSrc[i+2];
	    pGreen[j] = pSrc[i+1];
	    pBlue[j]  = pSrc[i];
	    j++;
	  }

      MDP_OSAL_MEMCPY((void*)pDst, (void*)pRed, uNumPixelPerPlanarRow);
	  MDP_OSAL_MEMCPY((void*)(pDst + uGreenDstStride), (void*)pGreen, uNumPixelPerPlanarRow);
	  MDP_OSAL_MEMCPY((void*)(pDst + uBlueDstStride), (void*)pBlue, uNumPixelPerPlanarRow);

      pDst += uDstStride;
      pSrc += uSrcStride;
    }
  }
  else
  {
	DEBUG((EFI_D_ERROR, "DisplayDxe: max fb width is less than required fb width\n"));
  }
}

/**
  Display DXE Internal Blit function for Planar formats
  
  @param  pSrc              Pointer (non NULL) to source buffer.
  @param  pdst              Pointer (non NULL) to destination buffer.                        

  @param  uSrcX             X coordinate of source.
  @param  uSrcY             Y coordinate of source.
  @param  uSrcWidth         Width of source rectangle in pixels.
  @param  uSrcHeight        Height of source rectangle in pixels.
  @param  uSrcStride        Stride of source rectangle in bytes.
  
  @param  uDstX             X coordinate of destination.
  @param  uDstY             Y coordinate of destination.
  @param  uDstWidth         Width of dest rectangle in pixels
  @param  uDstHeight        Height of dest rectangle in pixels
  @param  uDstStride        Stride of destination rectangle in bytes.

  @param  uBytesPerPixel    Number of bytes per pixel. 
  @param  ePixelFormat      Framebuffer format.
**/
static void DisplayDxeBlt (
  UINT8               *pSrc,
  UINT8               *pDst,
  UINTN                uSrcX,
  UINTN                uSrcY,
  UINTN                uSrcWidth,
  UINTN                uSrcHeight,
  UINTN                uSrcStride,
  UINTN                uDstX,
  UINTN                uDstY,
  UINTN                uDstWidth,
  UINTN                uDstHeight,
  UINTN                uDstStride,
  UINTN                uBytesPerPixel,
  MDP_PixelFormatType  ePixelFormat
  )
{
	
  switch (ePixelFormat)
  {
	case DISPLAYDXE_FSD_MDP_FORMAT:
	  DisplayDxeBltInternalPlanar (pSrc,
                                   pDst,
                                   uSrcX,
                                   uSrcY,
                                   uSrcWidth,
                                   uSrcHeight,
                                   uSrcStride,
                                   uDstX,
                                   uDstY,
                                   uDstWidth,
                                   uDstHeight,
                                   uDstStride,
                                   uBytesPerPixel);	 
	  break;
	default:
	  DisplayDxeBltInternal (pSrc,
                             pDst,
                             uSrcX,
                             uSrcY,
                             uSrcWidth,
                             uSrcHeight,
                             uSrcStride,
                             uDstX,
                             uDstY,
                             uDstStride,
                             uBytesPerPixel);
	  break;
  }
}

/**
FlushStaleLines

Check if Frame buffer is cached, and perform cache maintenance.

@param  pAddress            Start of frame buffer address
@param  uLength             Length of frame buffer need to write back from cache

@retval None

**/
static void FlushStaleLines(VOID *pAddress, uint32 uLength)
{
  if ((ARM_MEMORY_REGION_ATTRIBUTE_WRITE_BACK_XN == gDxeModeInfo.eDisplayFBAttrib) ||
      (ARM_MEMORY_REGION_ATTRIBUTE_WRITE_BACK    == gDxeModeInfo.eDisplayFBAttrib))
  {
    WriteBackDataCacheRange(pAddress, uLength);
  }
}


/**
GetChargerPowerStatus

Check charger power status using charger protocol.

@param  None

@retval EFI_SUCCESS       Charger power status is okay or no charger policy used for this platform
@retval other             Charger power status is not okay or at off mode charging

**/
static EFI_STATUS GetChargerPowerStatus(void)
{
  EFI_STATUS                eStatus            = EFI_SUCCESS;
  BOOLEAN                   bOffModeCharging   = FALSE;
  EFI_CHARGER_EX_PROTOCOL   *ChargerExProtocol = NULL;
  EFI_CHARGER_EX_FLASH_INFO sPowerTypeInfo     = {0};

  if (0 == PcdGet32(PcdDisplayChargerPolicy))
  {
    // Charger policy is not enforced on this platform
    eStatus = EFI_SUCCESS;
  }
  else
  {
    eStatus = gBS->LocateProtocol(&gChargerExProtocolGuid,
                                  NULL,
                                  (void**)&ChargerExProtocol);

    if ((EFI_SUCCESS != eStatus)                                                 ||
        (EFI_SUCCESS != ChargerExProtocol->IsOffModeCharging(&bOffModeCharging)) ||
        (EFI_SUCCESS != ChargerExProtocol->IsPowerOk(EFI_CHARGER_EX_POWER_FLASH_BATTERY_VOLTAGE_TYPE, &sPowerTypeInfo)))
    {
      // Unable to locate charger protocol, just continue with power okay status
      eStatus = EFI_SUCCESS;
    }
    else if((TRUE  == bOffModeCharging) ||
            (FALSE == sPowerTypeInfo.bCanFlash))
    {
      // Charger power status is not ok or at off mode charging
      eStatus = EFI_OUT_OF_RESOURCES;
    }
    else
    {
      // Charger power status is ok
      eStatus = EFI_SUCCESS;
    }
  }
  return eStatus;
}


/**
GetFirstAvailableDisplayId

Get the first available display id.

@param  None

@retval eDisplayId        Valid display id can be detected

**/
static MDP_Display_IDType GetFirstAvailableDisplayId(void)
{
  EFI_STATUS         eStatus    = EFI_DEVICE_ERROR;
  MDP_Display_IDType eDisplayId = MDP_DISPLAY_PRIMARY;

  for (eDisplayId = MDP_DISPLAY_PRIMARY; eDisplayId <= MDP_DISPLAY_EXTERNAL; eDisplayId++)
  {
    if (gDxeModeInfo.uNumModes[eDisplayId] > 0)
    {
      eStatus = EFI_SUCCESS;
      break;
    }
  }

  if (EFI_SUCCESS != eStatus)
  {
    eDisplayId = MDP_DISPLAY_PRIMARY;
  }

  return eDisplayId;
}


/**
  Display dxe thread for handling set mode

  @param  Args              Optional Args

**/
static INT32 SetModeThread(void *sArgs)
{
  DisplayDxe_SetMode (&gDisplayDxeOutputProtocol, 0);

  return 0;
}


/**
  Helper function to initialize the gSupportedDisplayList
**/
static bool32* DisplaySupportTableInit(void)
{
  uint32 uSupportedDisplays = PcdGet32(PcdSupportedDisplays);

  if (uSupportedDisplays > 0)
  {
    uint32 i;

    for (i = 0; i < MDP_DISPLAY_MAX; i++)
    {
      if (uSupportedDisplays & (1 << i))
      {
        gSupportedDisplayList[i] = TRUE;
      }
      else
      {
        gSupportedDisplayList[i] = FALSE;
      }
    }
  }
  
  return &gSupportedDisplayList[0];
}

/**
Helper function to update the gSupportedDisplayList

@param  pSupportedDisplay        Source supported display array.
@param  uSupportedDisplayLength  Length of source supported display array.

**/
static VOID UpdateSupportedDisplayList(bool32 *pSupportedDisplay, uint32 uSupportedDisplayLength)
{
  uint32 ugSupportedDisplayListLength = sizeof(gSupportedDisplayList) / sizeof(gSupportedDisplayList[0]);
  uint32 uCopyLength                  = (uSupportedDisplayLength < ugSupportedDisplayListLength) ? uSupportedDisplayLength : ugSupportedDisplayListLength;

  for (uint32 uIndex = 0; uIndex < uCopyLength; uIndex++)
  {
    gSupportedDisplayList[uIndex] = pSupportedDisplay[uIndex];
  }
}

/**
Helper function to divide by the frame buffer in to chunks based on number of inputs frame

Total Frame Buffer Size >= (Sc * Primary_resolution) + Padding + (Sc * Secondary_Resolution)
Padding                  = 256 byte alignment
Sc                       = Scale factor is adjusted to ensure Total frame buffer size is not exceeded.

@param  uFrameBufferBase        Frame buffer base address.
@param  uFrameBufferSize        Frame buffer size.
@param  pFrameBuffer            Frame buffer offset info.
@param  uNumBuffers             Number of buffers can be divided.

**/
static VOID CalculateFrameBufferOffsets(UINT64 uFrameBufferBase, UINT64 uFrameBufferSize, FrameBufferOffsetType *pFrameBuffer, UINT32 uNumBuffers)
{
  if ((0    == uFrameBufferBase) ||
      (0    == uFrameBufferSize) ||
      (NULL == pFrameBuffer)     ||
      (0    == uNumBuffers))
  {
    DEBUG((EFI_D_WARN, "DisplayDxe: CalculateFrameBufferOffsets invalid parameters are passed!\n"));
  }
  else if (1 == uNumBuffers)
  {
    pFrameBuffer[0].pFrameBufferStart  = (VOID *)uFrameBufferBase;
    pFrameBuffer[0].uFrameBufferLength = (UINT64)pFrameBuffer[0].uFrameWidth * pFrameBuffer[0].uFrameHeight * gDxeModeInfo.uBytesPerPixel;
  }
  else
  {
    UINT32  uBufferIndex              = 0x0;
    UINT64  uUnalignedFrameBufferBase = 0x0;
    UINT64  uDisplayBufferSize        = 0x0;

    pFrameBuffer[0].pFrameBufferStart = (VOID *)uFrameBufferBase;

    // Calculate all display buffer size.
    for(uBufferIndex = 0; uBufferIndex < uNumBuffers; uBufferIndex++)
    {
      pFrameBuffer[uBufferIndex].uFrameBufferLength  = ((pFrameBuffer[uBufferIndex].uFrameWidth) * (pFrameBuffer[uBufferIndex].uFrameHeight)) * gDxeModeInfo.uBytesPerPixel;
      uDisplayBufferSize                             = uDisplayBufferSize + pFrameBuffer[uBufferIndex].uFrameBufferLength;
    }
 
    // Re-calculate buffer offsets if all display buffer size exceeds the total buffer size.
    if (uDisplayBufferSize > uFrameBufferSize)
    {
      for(uBufferIndex = 0; uBufferIndex < uNumBuffers-1; uBufferIndex++)
      {
        // Calculate unaligned start address for uBufferIndex + 1 buffer based on uBufferIndex buffer start address and its buffer length.
        uUnalignedFrameBufferBase                         = (UINT64)pFrameBuffer[uBufferIndex].pFrameBufferStart +
                                                            MDP_CEIL((float)pFrameBuffer[uBufferIndex].uFrameBufferLength * uFrameBufferSize, uDisplayBufferSize);
        // Align start address for uBufferIndex + 1 buffer.
        pFrameBuffer[uBufferIndex + 1].pFrameBufferStart  = (VOID *) (MDP_DISPLAY_ALIGN(uUnalignedFrameBufferBase, MDP_ALIGN_256));

        // Calculate length for uBufferIndex buffer.
        pFrameBuffer[uBufferIndex].uFrameBufferLength     = (UINT64)pFrameBuffer[uBufferIndex + 1].pFrameBufferStart - (UINT64)pFrameBuffer[uBufferIndex].pFrameBufferStart;

        // Calculate length for the last part of framebuffer.
        if ((uNumBuffers - 2) == uBufferIndex)
        {
          pFrameBuffer[uNumBuffers - 1].uFrameBufferLength = uFrameBufferBase + uFrameBufferSize - (UINT64)pFrameBuffer[uNumBuffers - 1].pFrameBufferStart;
        }
      }
    }
    else
    {
      for(uBufferIndex = 0; uBufferIndex < uNumBuffers-1; uBufferIndex++)
      {
        // Calculate unaligned start address for uBufferIndex + 1 buffer based on uBufferIndex buffer start address and its buffer length.
        uUnalignedFrameBufferBase                        = (UINT64)pFrameBuffer[uBufferIndex].pFrameBufferStart +
                                                           pFrameBuffer[uBufferIndex].uFrameWidth * pFrameBuffer[uBufferIndex].uFrameHeight * gDxeModeInfo.uBytesPerPixel;
        // Align start address for uBufferIndex + 1 buffer.
        pFrameBuffer[uBufferIndex + 1].pFrameBufferStart = (VOID *) (MDP_DISPLAY_ALIGN(uUnalignedFrameBufferBase, MDP_ALIGN_256));

        // Calculate length for uBufferIndex buffer.
        pFrameBuffer[uBufferIndex].uFrameBufferLength    = pFrameBuffer[uBufferIndex].uFrameWidth * pFrameBuffer[uBufferIndex].uFrameHeight * gDxeModeInfo.uBytesPerPixel;

        // Calculate length for the last part of framebuffer.
        if ((uNumBuffers - 2) == uBufferIndex)
        {
          pFrameBuffer[uNumBuffers - 1].uFrameBufferLength   = pFrameBuffer[uNumBuffers - 1].uFrameWidth * pFrameBuffer[uNumBuffers - 1].uFrameHeight * gDxeModeInfo.uBytesPerPixel;

          // If aligned last framebuffer end address exceeds the total buffer end address, then re-calculate framebuffer size.
          if (((UINT64)(pFrameBuffer[uNumBuffers -1].pFrameBufferStart) + pFrameBuffer[uNumBuffers - 1].uFrameBufferLength) > (uFrameBufferBase + uFrameBufferSize))
          {
            pFrameBuffer[uNumBuffers - 1].uFrameBufferLength = uFrameBufferBase + uFrameBufferSize - (UINT64)pFrameBuffer[uNumBuffers - 1].pFrameBufferStart;
          }
        }
      }
    }
  }
}

/**
Helper function to get the frame buffer info.

@param  eDisplayId              Display ID.
@param  pFrameBuffer            Frame buffer info.

@retval EFI_STATUS
**/
static EFI_STATUS GetFrameBufferInfo(MDP_Display_IDType eDisplayId, FrameBufferOffsetType *pFrameBuffer)
{
  EFI_STATUS  eStatus = EFI_SUCCESS;

  if (NULL == pFrameBuffer)
  {
    DEBUG((EFI_D_WARN, "DisplayDxe: GetFrameBufferInfo pFrameBuffer is NULL!\n"));
    eStatus = EFI_INVALID_PARAMETER;
  }
  else if (eDisplayId >= FRAMEBUFFER_MAX_NUMBER)
  {
    // Just return primary buffer info if eDisplayId is out of range.
    MDP_OSAL_MEMCPY(pFrameBuffer, &gDxeModeInfo.aFrameBuffers[0], sizeof(FrameBufferOffsetType));
  }
  else
  {
    MDP_OSAL_MEMCPY(pFrameBuffer, &gDxeModeInfo.aFrameBuffers[eDisplayId], sizeof(FrameBufferOffsetType));
  }

  return eStatus;
}
