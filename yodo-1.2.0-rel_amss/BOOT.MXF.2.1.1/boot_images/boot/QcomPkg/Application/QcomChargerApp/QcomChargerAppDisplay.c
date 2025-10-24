/** @file QcomChargerAppDisplay.c

  Helper functions for displaying images on screen

  Copyright (c) 2019, Qualcomm Technologies Inc. All rights reserved.

**/

/*=============================================================================
                              EDIT HISTORY


 when         who     what, where, why
 --------     ---     -----------------------------------------------------------
 01/28/19     kpa     Support loading bmp src's from guided fv
 03/13/19     pbitra  Initial revision

=============================================================================*/
#include <Uefi.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiRuntimeServicesTableLib.h>
#include <Library/DebugLib.h>
#include <Library/QcomLib.h>
#include <Library/BMPLib.h>
#include "Library/SerialPortShLib.h"
#include <Library/QcomTargetLib.h>
#include <Library/FuseControlLib.h>
#include <api/pmic/pm/pm_uefi.h>
#include <Library/MountFvLib.h>

#include <Protocol/EFIDisplayPwr.h>
#include <Protocol/EFIDisplayPwrCtrl.h>
#include <Protocol/EFIClock.h>

#include <Protocol/GraphicsOutput.h>

#include <Library/UefiLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/ParserLib.h>
#include <Library/BaseMemoryLib.h>
#include <Guid/FileSystemInfo.h>
#include <Guid/FileInfo.h>

#include "DDIPlatformInfo.h"
#include <Protocol/SimpleFileSystem.h>
#include <Protocol/EFIDisplayUtils.h>
#include <Protocol/EFIPIL.h>

#include "QcomChargerAppDisplay.h"

#ifdef FEATURE_XBOOT
#include <Library/XBootDisplayLib.h>
#endif /* FEATURE_XBOOT */

#ifndef FEATURE_XBOOT
extern EFI_GUID gEfiImageFvNameGuid;
STATIC BOOLEAN ImageFvLoadedFlag = FALSE;
#endif /* !FEATURE_XBOOT */

/******************************************************************************
            LOCAL FUNCTIONS
******************************************************************************/
extern EFI_STATUS
LoadFromFV(IN   CHAR8 *Name,
           OUT  UINT8 **FileBuffer,
           OUT  UINTN *FileSize);

STATIC EFI_STATUS QcomChargeAppDisplay_ClearScreen( void );

/**
  Duplicates ASCII string

  @param  Source  Null Terminated string of characters
  @param  Length  source String length
  @return  Duplicated String  if successful otherwise return NULL

  note: Caller responsibility to Free returned String
**/
EFI_STATUS QcomChargerAppDisplay_AsciiStrNDup(
  CONST CHAR8               *Source,
  CHAR8*                     Dest,
  UINTN                     Length
)
{
  if(NULL == Source || 0 == Length || Dest == NULL)
    return EFI_INVALID_PARAMETER;
  AsciiStrnCpyS(Dest, Length+1 ,Source, Length + 1);

  return EFI_SUCCESS;
}

/* API to clear the display screen */
EFI_STATUS QcomChargeAppDisplay_ClearScreen( void )
{
  EFI_STATUS                              Status = EFI_SUCCESS;
  STATIC EFI_GRAPHICS_OUTPUT_PROTOCOL    *pGfxProtocol = NULL;
  EFI_GUID                                sGfxOutputGUID = EFI_GRAPHICS_OUTPUT_PROTOCOL_GUID;
  EFI_GRAPHICS_OUTPUT_MODE_INFORMATION   *pModeInfo = NULL;
  UINTN                                   nModeInfoSize = 0;
  EFI_GRAPHICS_OUTPUT_BLT_PIXEL           bgPixel = {0, 0, 0, 0};
  UINT32                                  mode = 0;

  if(!pGfxProtocol)
  {
    Status = gBS->LocateProtocol ( &sGfxOutputGUID,
                                   NULL,
                                   (VOID **)&pGfxProtocol);
  }

  if (EFI_SUCCESS != Status)
  {
    DEBUG((EFI_D_ERROR, "QcomChargerApp:: %a ChgAppClearScreen LocateProtocol(pGfxProtocol) failed. Status = %r \r\n", __FUNCTION__, Status));
    return Status;
  }

  if (EFI_SUCCESS != (Status = pGfxProtocol->SetMode(pGfxProtocol, mode)))
  {
    DEBUG((EFI_D_ERROR, "QcomChargerApp:: %a ChgAppClearScreen SetMode() failed. Status = %r \r\n",__FUNCTION__, Status));
    return Status;
  }

  if (EFI_SUCCESS != (Status = pGfxProtocol->QueryMode(pGfxProtocol, 0, &nModeInfoSize, &pModeInfo)))
  {
    DEBUG((EFI_D_ERROR, "QcomChargerApp:: %a ChgAppClearScreen QueryMode() failed.Status = %r  \r\n",__FUNCTION__, Status));
    return Status;
  }

  /* Fill background as black */
  bgPixel.Blue     = 0x00;
  bgPixel.Green    = 0x00;
  bgPixel.Red      = 0x00;
  bgPixel.Reserved = 0x00;

  Status = pGfxProtocol->Blt( pGfxProtocol,
                              (EFI_GRAPHICS_OUTPUT_BLT_PIXEL*)&bgPixel,
                              EfiBltVideoFill,
                              0, 0,
                              0, 0,
                              pModeInfo->HorizontalResolution,
                              pModeInfo->VerticalResolution,
                              0);

  if (EFI_SUCCESS != Status)
  {
    DEBUG((EFI_D_ERROR, "QcomChargerApp:: %a ChgAppClearScreen Blt(EfiBltVideoFill)  failed.Status = %r \r\n",__FUNCTION__, Status));
    return Status;
  }

  return Status;

}

EFI_STATUS QcomChargerAppDisplay_DispBattSymbol(EFI_QCOM_CHARGER_DISP_IMAGE_TYPE DispImage, BOOLEAN ClearScreen)
{
#ifdef FEATURE_XBOOT
  EFI_STATUS Status = EFI_SUCCESS;

  switch (DispImage)
  {
  case EFI_QCOM_CHARGER_DISP_IMAGE_LOWBATTERYCHARGING:
    Status = XBootDisplayDraw("DeadBatteryCharging");
    if (Status != EFI_SUCCESS) {
      DEBUG((EFI_D_ERROR, "XBootDisplayDraw(DeadBatteryCharging) returned error %d\n", Status));
    }
    break;
  case EFI_QCOM_CHARGER_DISP_IMAGE_LOWBATTERY:
  case EFI_QCOM_CHARGER_DISP_IMAGE_NOBATTERY:
  case EFI_QCOM_CHARGER_DISP_IMAGE_NOCHARGER:
    Status = XBootDisplayDraw("DeadBatteryNoCharging");
    if (Status != EFI_SUCCESS) {
      DEBUG((EFI_D_ERROR, "XBootDisplayDraw(DeadBatteryNoCharging) returned error %d\n", Status));
    }
    break;
  case EFI_QCOM_CHARGER_DISP_IMAGE_ABOVE_THRESHOLD:
    Status = QcomChargeAppDisplay_ClearScreen();
    if (Status != EFI_SUCCESS) {
      DEBUG((EFI_D_ERROR, "XBootDisplayDraw(ClearScreen) returned error %d\n", Status));
    }
    break;
  case EFI_QCOM_CHARGER_DISP_IMAGE_TSENS_THERMAL_SYMBOL:
  case EFI_QCOM_CHARGER_DISP_IMAGE_TSENS_CRITICAL_SYMBOL:
  case EFI_QCOM_CHARGER_DISP_IMAGE_DEBUG_BOOT_SYMBOL:
  case EFI_QCOM_CHARGER_DISP_IMAGE_DEBUG_LOW_SYMBOL:
  default:
    DEBUG((EFI_D_ERROR, "ChargerLib:: %a: no DisplayImage for %d\n", __FUNCTION__, DispImage));
    break;
  }
#else /* !FEATURE_XBOOT */
  EFI_STATUS Status = EFI_SUCCESS;
  EFI_PIL_PROTOCOL  *PILProtocol = NULL;
  char   *str = NULL;  

  switch (DispImage)
  {
  case EFI_QCOM_CHARGER_DISP_IMAGE_ABOVE_THRESHOLD:
    str = AllocatePool (AsciiStrLen(CHARGER_BATTERY_SYMBOL_ABOVE_THRESHOLD) + 1);
    Status = QcomChargerAppDisplay_AsciiStrNDup(CHARGER_BATTERY_SYMBOL_ABOVE_THRESHOLD, str, AsciiStrLen(CHARGER_BATTERY_SYMBOL_ABOVE_THRESHOLD));
    break;
  case EFI_QCOM_CHARGER_DISP_IMAGE_NOBATTERY:
    str = AllocatePool (AsciiStrLen(CHARGER_BATTERY_SYMBOL_NOBATTERY) + 1);
    Status = QcomChargerAppDisplay_AsciiStrNDup(CHARGER_BATTERY_SYMBOL_NOBATTERY, str, AsciiStrLen(CHARGER_BATTERY_SYMBOL_NOBATTERY));
    break;
  case EFI_QCOM_CHARGER_DISP_IMAGE_NOCHARGER:
    str = AllocatePool (AsciiStrLen(CHARGER_BATTERY_SYMBOL_NOCHARGER) + 1);
    Status =  QcomChargerAppDisplay_AsciiStrNDup(CHARGER_BATTERY_SYMBOL_NOCHARGER, str, AsciiStrLen(CHARGER_BATTERY_SYMBOL_NOCHARGER));
    break;
  case EFI_QCOM_CHARGER_DISP_IMAGE_LOWBATTERYCHARGING:
    str = AllocatePool (AsciiStrLen(CHARGER_BATTERY_SYMBOL_LOWBATTERYCHARGING) + 1);
    Status =  QcomChargerAppDisplay_AsciiStrNDup(CHARGER_BATTERY_SYMBOL_LOWBATTERYCHARGING, str, AsciiStrLen(CHARGER_BATTERY_SYMBOL_LOWBATTERYCHARGING));
    break;
  case EFI_QCOM_CHARGER_DISP_IMAGE_LOWBATTERY:
    str = AllocatePool (AsciiStrLen(CHARGER_BATTERY_SYMBOL_LOWBATTERY) + 1);
    Status = QcomChargerAppDisplay_AsciiStrNDup(CHARGER_BATTERY_SYMBOL_LOWBATTERY, str, AsciiStrLen(CHARGER_BATTERY_SYMBOL_LOWBATTERY));
    break;
  case EFI_QCOM_CHARGER_DISP_IMAGE_TSENS_THERMAL_SYMBOL:
    str = AllocatePool (AsciiStrLen(CHARGER_TSENS_THERMAL_SYMBOL) + 1);
    Status = QcomChargerAppDisplay_AsciiStrNDup(CHARGER_TSENS_THERMAL_SYMBOL, str, AsciiStrLen(CHARGER_TSENS_THERMAL_SYMBOL));
    break;
  case EFI_QCOM_CHARGER_DISP_IMAGE_TSENS_CRITICAL_SYMBOL:
    str = AllocatePool (AsciiStrLen(CHARGER_TSENS_CRITICAL_SYMBOL) + 1);
    Status = QcomChargerAppDisplay_AsciiStrNDup(CHARGER_TSENS_CRITICAL_SYMBOL, str, AsciiStrLen(CHARGER_TSENS_CRITICAL_SYMBOL));
    break;
  case EFI_QCOM_CHARGER_DISP_IMAGE_DEBUG_BOOT_SYMBOL:
    str = AllocatePool (AsciiStrLen(CHARGER_BATTERY_SYMBOL_DEBUG_BOARD_BOOT) + 1);
    Status = QcomChargerAppDisplay_AsciiStrNDup(CHARGER_BATTERY_SYMBOL_DEBUG_BOARD_BOOT, str, AsciiStrLen(CHARGER_BATTERY_SYMBOL_DEBUG_BOARD_BOOT));
    break;
  case EFI_QCOM_CHARGER_DISP_IMAGE_DEBUG_LOW_SYMBOL:
    str = AllocatePool (AsciiStrLen(CHARGER_BATTERY_SYMBOL_DEBUG_BOARD_STAY) + 1);
    Status = QcomChargerAppDisplay_AsciiStrNDup(CHARGER_BATTERY_SYMBOL_DEBUG_BOARD_STAY, str, AsciiStrLen(CHARGER_BATTERY_SYMBOL_DEBUG_BOARD_STAY));
    break;
  default:
    break;
  }

  /*Clear Screen when requested*/
  if(TRUE == ClearScreen)
  {
    if (EFI_SUCCESS != (Status = QcomChargeAppDisplay_ClearScreen()))
    {
      DEBUG((EFI_D_ERROR, "QcomChargerApp:: %a ChgAppClearScreen() returned error = %r\n\r", __FUNCTION__,Status));
    }
    /* CHARGER_DEBUG((EFI_D_ERROR, "QcomChargerApp: QcomChargerAppEvent_DispBattSymbol ChgAppClearScreen Cleared: %d\n\r", Status)); */
  }

   if(ImageFvLoadedFlag == FALSE)
   {
     Status = gBS->LocateProtocol (&gEfiPilProtocolGuid,NULL, (VOID **) &PILProtocol);
     if ((EFI_SUCCESS != Status) || (NULL == PILProtocol))
     {
       DEBUG(( EFI_D_ERROR, "ChargerLib:: %a %r \r\n", __FUNCTION__, Status));
       return Status;
     }

     Status = PILProtocol->ProcessPilImage(L"ImageFv");
     if ((EFI_SUCCESS != Status))
     {
       DEBUG(( EFI_D_ERROR, "ChargerLib:: %a %r \r\n", __FUNCTION__, Status));
       return Status;
     }
     ImageFvLoadedFlag = TRUE;
   }

  // /* Draw BMP image with default options, the screen will be cleared and the image
  //    will be drawn at the center of the screen*/
  Status = DrawBmpFile(str, NULL, 0, &gEfiImageFvNameGuid);

  if(NULL != str )
  {
    FreePool(str);
    str = NULL;
  }
#endif /* !FEATURE_XBOOT */

  return Status;
}

