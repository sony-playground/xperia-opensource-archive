/*============================================================================
  FILE:         PASRDxe.c

  OVERVIEW:     Implementation of the PASR EFI protocol interface

  DEPENDENCIES: None

                Copyright (c) 2022 Qualcomm Technologies, Inc.
                All Rights Reserved.
                Qualcomm Technologies Confidential and Proprietary,
============================================================================*/
/*============================================================================
  EDIT HISTORY FOR MODULE

  This section contains comments describing changes made to the module.
  Notice that changes are listed in reverse chronological order.  Please
  use ISO format for dates.

  when        who      what, where, why
  ----------  ---      -----------------------------------------------------------
  2022-05-12  daisond  Initial revision.

============================================================================*/
/*----------------------------------------------------------------------------
 * Include Files
 * -------------------------------------------------------------------------*/
#include <Uefi.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/DebugLib.h>
#include <Library/PASRLib.h>
#include <Library/UefiLib.h>
#include <Library/LockLib.h>
#include <Protocol/EFIPasr.h>

/*----------------------------------------------------------------------------
 * Type Declarations
 * -------------------------------------------------------------------------*/
static EFI_EVENT Pasr_Event;
LockHandle* PasrLock;

/*----------------------------------------------------------------------------
 * Static Function Declarations
 * -------------------------------------------------------------------------*/

/*===========================================================================*/

static EFI_STATUS
EFI_PasrConfig(
    IN EFI_PASR_PROTOCOL *This,
    IN UINT32 Num_Blocks,
    IN PASR_BLOCK *Pasr_Block); 

static EFI_STATUS
EFI_PASRActivate(
    IN EFI_PASR_PROTOCOL *This);
/*==============================================================================

  FUNCTION      EFI_PasrConfig

  DESCRIPTION   See EFI_PASR_CONFIG in Protocol/EFIPasr.h

==============================================================================*/
EFI_STATUS
EFI_PasrConfig(
    IN EFI_PASR_PROTOCOL *This,
    IN UINT32 Num_Blocks,
    IN PASR_BLOCK *Pasr_Block) 
{
  EFI_STATUS Status = EFI_SUCCESS;

  Status = PasrConfig(Num_Blocks, Pasr_Block);
  if (Status != EFI_SUCCESS)
    return EFI_UNSUPPORTED;

  return Status;
}

/*==============================================================================

  FUNCTION      EFI_PASRActivate

  DESCRIPTION   See EFI_PASRActivate in Protocol/EFIPasr.h

==============================================================================*/
EFI_STATUS
EFI_PASRActivate(
    IN EFI_PASR_PROTOCOL *This)
{
  EFI_STATUS Status = EFI_SUCCESS;
  
  AcquireLock (PasrLock);
  Status = PASRActivate();
  ReleaseLock (PasrLock);
  
  if (Status != EFI_SUCCESS)
    return EFI_UNSUPPORTED;

  return Status;
}

STATIC EFI_PASR_PROTOCOL PASRProtocol = 
{
  EFI_PASR_PROTOCOL_REVISION_V1,
  EFI_PasrConfig,
  EFI_PASRActivate,
};

/*==============================================================================

  FUNCTION      SetNominalDDRFreq

  DESCRIPTION   Register for npa resource callback for "icb/arbiter"

==============================================================================*/

VOID
EFIAPI
PASRActivate_CB (
  IN EFI_EVENT  Event,
  IN VOID       *Context
  )
{
  EFI_STATUS Status = EFI_SUCCESS;
  
  AcquireLock (PasrLock);
  Status = PASRActivate();
  ReleaseLock (PasrLock);
  
  if ((EFI_ERROR(Status)))
  {
      DEBUG((EFI_D_ERROR, "PASRActivate failed, Status : 0x%x \r\n", Status));
  }
  // Only do this once.
  gBS->CloseEvent(Pasr_Event);
}


/*----------------------------------------------------------------------------
 * Externalized Function Definitions
 * -------------------------------------------------------------------------*/
EFI_STATUS
EFIAPI
PASRDxeEntryPoint(IN EFI_HANDLE ImageHandle, IN EFI_SYSTEM_TABLE *SystemTable)
{
   EFI_STATUS Status = EFI_SUCCESS;
   Status = InitLock(NULL, &PasrLock);
   if (EFI_ERROR(Status) || PasrLock==NULL) 
   {
      DEBUG ((EFI_D_ERROR, "Failed to init PASR lock\n"));
      return Status;
   }
   
   Status = gBS->InstallMultipleProtocolInterfaces (&ImageHandle, 
                                 &gEfiPasrProtocolGuid, 
                                 &PASRProtocol, 
                                 NULL, NULL);
   /* Register for the callback which will be set by ChargerDxe */
   Status = gBS->CreateEventEx (
                  EVT_NOTIFY_SIGNAL,
                  TPL_CALLBACK,
                  PASRActivate_CB,
                  NULL,
                  &gEfiEventPASRActivateGuid,
                  &Pasr_Event);
   /* Signal the event by ChargerDxe  Status = EfiEventGroupSignal(&gEfiEventPASRActivateGuid); */
  if ((EFI_ERROR(Status)))
  {
      DEBUG((EFI_D_ERROR, "PASRcallback registration failed, Status : 0x%x \r\n", Status));
  }
   return Status;
}

