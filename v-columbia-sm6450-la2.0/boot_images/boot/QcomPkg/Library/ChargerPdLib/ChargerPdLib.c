/** @file ChargerPdLib.c

  Provide access to Qcom Charger Protocol APIs

  Copyright (c) 2021, Qualcomm Technologies Inc. All rights reserved.

**/

/*=============================================================================
                              EDIT HISTORY


 when         who     what, where, why
 --------     ---     ---------------------------------------------------------
03/09/21      ns      Initial revision
=============================================================================*/

/*===========================================================================*/
/*                  INCLUDE FILES                                            */
/*===========================================================================*/
#include <Uefi.h>

/**
  Library Dependencies
*/
#include <Library/UefiBootServicesTableLib.h>
#include <Library/ChargerPdLib.h>
#include <Protocol/EFIQcomCharger.h>

STATIC EFI_QCOM_CHARGER_PROTOCOL        *pQcomChargerProtocol  = NULL;
STATIC BOOLEAN LoadChargerFwFlag = FALSE;

VOID StartCharger(VOID)
{
  EFI_STATUS                     Status = EFI_SUCCESS;
  EFI_QCOM_CHARGER_ACTION_INFO   ChargerActionInfo = {0};
  
  Status = gBS->LocateProtocol( &gQcomChargerProtocolGuid, NULL, (VOID **)&pQcomChargerProtocol );
  if(EFI_SUCCESS != Status || !pQcomChargerProtocol)
  {
    DEBUG(( EFI_D_ERROR, "%a Cannot locate Charger Protocol = %r \r\n", __FUNCTION__, Status));
    return;
  }

  /* Load Charger FW */
  Status |= pQcomChargerProtocol->TakeAction(EFI_QCOM_CHARGER_ACTION_LOAD_CHARGER_FW, &ChargerActionInfo);
  if(EFI_SUCCESS == Status)
  {
    /* Connect Charger FW */
    Status |= pQcomChargerProtocol->TakeAction(EFI_QCOM_CHARGER_ACTION_CONNECT_CHARGER_FW, &ChargerActionInfo);
    if(EFI_SUCCESS == Status)
    {
      LoadChargerFwFlag = TRUE;
    }
  }
}


VOID StopCharger(VOID)
{
  EFI_STATUS Status = EFI_SUCCESS;

  if(LoadChargerFwFlag)
  {
    if(!pQcomChargerProtocol)
    {
      Status = gBS->LocateProtocol( &gQcomChargerProtocolGuid, NULL, (VOID **)&pQcomChargerProtocol );
    }

    if((EFI_SUCCESS == Status) && (pQcomChargerProtocol))
    {
      Status = pQcomChargerProtocol->ChargerPDLogTimerExit(EFI_QCOM_CHARGER_ACTION_EXIT);
      LoadChargerFwFlag = FALSE;
    }
  }
}