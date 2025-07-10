/** @file ICBDxe.c

  This file implements ICB EFI protocol interface.
  Copyright (c) 2017 - 2021 Qualcomm Technologies, Inc. All rights reserved.

**/

/*=============================================================================
                              EDIT HISTORY


 when         who     what, where, why
 ----------   ---     -----------------------------------------------------------
 03/01/2021   sds     Enable post_init in callback.
 03/18/2020   sds     Created.

=============================================================================*/


/*=========================================================================
      Include Files
==========================================================================*/

#include <Uefi.h>
#include <Guid/EventGroup.h>
#include <Library/BaseLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/DebugLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/CacheMaintenanceLib.h>
#include <Protocol/EFIDALSYSProtocol.h>
#include <Protocol/EFIICB.h>
#include <api/systemdrivers/icbarb.h>
#include <api/systemdrivers/coreinit.h>
#include <Library/QcomTargetLib.h>
#include <Library/QcomLib.h>
#include <api/dal/DALSys.h>

/*=========================================================================
      Type Definitions
==========================================================================*/


/*=========================================================================
      Function Prototypes
==========================================================================*/

EFI_STATUS EFI_PostInit(IN EFI_ICB_PROTOCOL *This);

/*=========================================================================
      Data Declarations
==========================================================================*/

// ICB Public Protocol
static EFI_ICB_PROTOCOL ICBProtocol =
{
   EFI_ICB_PROTOCOL_VERSION,
   EFI_PostInit,
 };


// Ready to boot event
static EFI_EVENT event;

/*==============================================================================

                     GLOBAL VARIABLES FOR THIS MODULE

==============================================================================*/
DALProps gDALModStringDeviceInfoList = {NULL, 0 ,0 , NULL};

static DALSYSConfig DALSYSModConfig =
   {
      {0, NULL},              // string device info
      {0, NULL}   // numeric driver info
   };

/*=========================================================================
      Functions
==========================================================================*/
/**
  Allow flush of all zero bandwidth nodes.

  @par Description
    @param  This      [in]  The EFI_ICB_PROTOCOL instance.
 
  @return
  EFI_SUCCESS        -- Function completed successfully. \n
  EFI_PROTOCOL_ERROR -- Error occurred during the operation.
*/
EFI_STATUS
EFI_PostInit(
  IN EFI_ICB_PROTOCOL *This
)
{
  /* Flush all votes for zero. */
  icbarb_post_init();

  return EFI_SUCCESS;
}


/**
  Notify function for event group EFI_EVENT_GROUP_READY_TO_BOOT. This is used to
  trigger default voting and icbarb_post_init().

  @param[in]  Event   The Event that is being processed.
  @param[in]  Context The Event Context.

**/
VOID
EFIAPI
ICBReadyToBootEventNotify (
  IN EFI_EVENT         Event,
  IN VOID             *Context
  )
{
  /* Put in our proxy votes. */
  coreinit_init();

  /* Flush and sync BCM hardware state. */
  icbarb_post_init();

  // Only do this once.
  gBS->CloseEvent(event);
}

/**
  ICB DXE driver entry point.

  @param[in] ImageHandle    The firmware allocated handle for the EFI image.
  @param[in] SystemTable    A pointer to the EFI System Table.

  @retval EFI_SUCCESS       The entry point is executed successfully.
  @retval other             Some error occurs when executing this entry point.

**/

EFI_STATUS
EFIAPI
ICBDxeEntryPoint (
  IN EFI_HANDLE        ImageHandle,
  IN EFI_SYSTEM_TABLE *SystemTable
  )
{
  EFI_HANDLE  handle = NULL;
  EFI_STATUS  status;

  (void)ImageHandle;
  (void)SystemTable;

  // Init DALSys
  DALSYS_InitMod(&DALSYSModConfig);

  // Init IcbArb which needs to happen after NPA/CMDDB/RPMh drivers are initialized 
  icbarb_init();

  // Publish the ICB Protocol
  status = gBS->InstallMultipleProtocolInterfaces(
              &handle,
              &gEfiICBProtocolGuid,
              (void **)&ICBProtocol,
              NULL );
  //
  // Register notify function to install Esrt Table on ReadyToBoot Event.
  //
  status = gBS->CreateEventEx(
                  EVT_NOTIFY_SIGNAL,
                  TPL_CALLBACK,
                  ICBReadyToBootEventNotify,
                  NULL,
                  &gEfiEventICBPostInitGuid,
                  &event);

  return status;
}

