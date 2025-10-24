/** @file
                    SecBootSigLib.c

  SecBootSigLib driver is responsible for providing signal interface to measurement
  or authentication.

  This file is platform independent, it needs to work with platform(target)
  dependent driver part.

  Copyright (c) 2013, 2015, 2020, 2022 Copyright Qualcomm Technologies, Inc.
  All Rights Reserved.

**/

/*=============================================================================
                              EDIT HISTORY
  This section contains comments describing changes made to the module.
  Notice that changes are listed in reverse chronological order.



 when       who      what, where, why
--------   ---      ----------------------------------------------------------
06/24/20   shl      Added measure boot test event.
07/13/15   al       Changing TPL_NOTIFY to TPL_CALLBACK
12/10/13   sm       Updated print statements
05/15/12   shl      Added support for OEM FW update
12/16/11   shl      Added MorPpi feature 
11/28/11   shl      Separate BdsPlatform from library lingking.
11/24/11   shl      Added measure boot support 
08/18/11   shl      Initial version

=============================================================================*/
#include <Uefi.h>
#include <MacroUtility.h>
#include <Library/DebugLib.h>
#include <Library/UefiBootServicesTableLib.h>

// event to signal
EFI_EVENT  SecBootRegEvent1;
EFI_EVENT  MeasureBootRegEvent1;
EFI_EVENT  MeasureBootStartEvent1;
EFI_EVENT  MeasureBootTestEvent1;
EFI_EVENT  MeasureReturnFromEfiAppFromBootOptionEvent1;
EFI_EVENT  MorPpiEvent1;
EFI_EVENT  OemFwUpdateEvent1;

//Event Guid
EFI_GUID gQcomSecBootRegEventGuid       = { 0x1d2d1996, 0xc860, 0x4640, { 0xb7, 0xa0, 0xe2, 0xe3, 0x30, 0x9e, 0x70, 0x87 } };
EFI_GUID gQcomMeasureBootRegEventGuid   = { 0x317b2dc1, 0x898,  0x4897, { 0xb1, 0x4f, 0x4e, 0xae, 0xc2, 0x82, 0xf7, 0x7f } };
EFI_GUID gQcomMeasureBootStartEventGuid = { 0x73164d70, 0xd19b, 0x48cc, { 0xa8, 0x71, 0x5e, 0x48, 0x5d, 0xa8, 0x99, 0x8a } };
EFI_GUID gQcomMeasureBootTestEventGuid  = { 0xba9293b3, 0x5d59, 0x41cc, { 0xa7, 0x12, 0x1, 0x3, 0x32, 0xd7, 0xf, 0x84 } };
EFI_GUID gQcomMeasureReturnFromEfiAppFromBootOptionEventGuid = { 0xce19f251, 0x6f1d, 0x4ffa, { 0x8d, 0xf5, 0xb9, 0xbf, 0xc0, 0x9, 0x9d, 0x92 } };
EFI_GUID gQcomMorPpiEventGuid           = { 0xccf447c0, 0x910b, 0x49e0, { 0xab, 0xcc, 0xdf, 0x3a, 0xa, 0x95, 0xff, 0x70 } };
EFI_GUID gQcomOemFwUpdateEventGuid      = { 0xccd86915, 0xccf7, 0x4b9a, { 0xaf, 0x7b, 0x41, 0x94, 0xa8, 0xc9, 0xad, 0x44 } };


VOID EFIAPI SecBootDummyHandler
(
  IN EFI_EVENT   Event, 
  IN VOID       *Context
)
{
  return;
}


EFI_STATUS
EFIAPI
SetSecBootRegSignal( VOID )
{
  EFI_STATUS  Status;
 
  // create an event, when this envent is signaled, a verification funcion will be registered.
  Status = gBS->CreateEventEx ( EVT_NOTIFY_SIGNAL,
                                TPL_CALLBACK,
                                SecBootDummyHandler,
                                NULL,
                               &gQcomSecBootRegEventGuid,
                               &SecBootRegEvent1);
  EXIT_IF_TRUE( Status );

  Status = gBS->SignalEvent( SecBootRegEvent1 );
  EXIT_IF_TRUE( Status );

  Status = gBS->CloseEvent( SecBootRegEvent1);
  EXIT_IF_TRUE( Status );

ErrorExit:
  return Status;

}


EFI_STATUS
EFIAPI
SetMeasureBootRegSignal( VOID )
{
  EFI_STATUS  Status;
 
  // create an event, when this envent is signaled, a verification funcion will be registered.
  Status = gBS->CreateEventEx ( EVT_NOTIFY_SIGNAL,
                                TPL_CALLBACK,
                                SecBootDummyHandler,
                                NULL,
                               &gQcomMeasureBootRegEventGuid,
                               &MeasureBootRegEvent1);
  EXIT_IF_TRUE( Status );

  Status = gBS->SignalEvent( MeasureBootRegEvent1 );
  EXIT_IF_TRUE( Status );

  Status = gBS->CloseEvent( MeasureBootRegEvent1);
  EXIT_IF_TRUE( Status );

ErrorExit:
  return Status;

}


EFI_STATUS
EFIAPI
SetMeasureBootStartSignal( VOID )
{
  EFI_STATUS  Status;
 
  // create an event, when this envent is signaled, a verification funcion will be registered.
  Status = gBS->CreateEventEx ( EVT_NOTIFY_SIGNAL,
                                TPL_CALLBACK,
                                SecBootDummyHandler,
                                NULL,
                               &gQcomMeasureBootStartEventGuid,
                               &MeasureBootStartEvent1);
  EXIT_IF_TRUE( Status );

  Status = gBS->SignalEvent( MeasureBootStartEvent1 );
  EXIT_IF_TRUE( Status );

  Status = gBS->CloseEvent( MeasureBootStartEvent1);
  EXIT_IF_TRUE( Status );

ErrorExit:
  return Status;

}


EFI_STATUS
EFIAPI
SetMeasureBootTestSignal( VOID )
{
  EFI_STATUS  Status;
 
  // create an event, when this envent is signaled, a verification funcion will be registered.
  Status = gBS->CreateEventEx ( EVT_NOTIFY_SIGNAL,
                                TPL_CALLBACK,
                                SecBootDummyHandler,
                                NULL,
                               &gQcomMeasureBootTestEventGuid,
                               &MeasureBootTestEvent1);
  EXIT_IF_TRUE( Status );

  Status = gBS->SignalEvent( MeasureBootTestEvent1 );
  EXIT_IF_TRUE( Status );

  Status = gBS->CloseEvent( MeasureBootTestEvent1);
  EXIT_IF_TRUE( Status );

ErrorExit:
  return Status;

}


EFI_STATUS
EFIAPI
SetMeasureReturnFromEfiAppFromBootOptionSignal( VOID )
{
  EFI_STATUS  Status;
 
  // create an event, when this envent is signaled, a verification funcion will be registered.
  Status = gBS->CreateEventEx ( EVT_NOTIFY_SIGNAL,
                                TPL_CALLBACK,
                                SecBootDummyHandler,
                                NULL,
                               &gQcomMeasureReturnFromEfiAppFromBootOptionEventGuid,
                               &MeasureReturnFromEfiAppFromBootOptionEvent1);
  EXIT_IF_TRUE( Status );

  Status = gBS->SignalEvent( MeasureReturnFromEfiAppFromBootOptionEvent1 );
  EXIT_IF_TRUE( Status );

  Status = gBS->CloseEvent( MeasureReturnFromEfiAppFromBootOptionEvent1);
  EXIT_IF_TRUE( Status );

ErrorExit:
  return Status;

}


EFI_STATUS
EFIAPI
SetMorPpiSignal( VOID )
{
  EFI_STATUS  Status;
 
  // create an event, when this envent is signaled, a verification funcion will be registered.
  Status = gBS->CreateEventEx ( EVT_NOTIFY_SIGNAL,
                                TPL_CALLBACK,
                                SecBootDummyHandler,
                                NULL,
                               &gQcomMorPpiEventGuid,
                               &MorPpiEvent1);
  EXIT_IF_TRUE( Status );

  Status = gBS->SignalEvent( MorPpiEvent1 );
  EXIT_IF_TRUE( Status );

  Status = gBS->CloseEvent( MorPpiEvent1);
  EXIT_IF_TRUE( Status );

ErrorExit:
  return Status;

}

EFI_STATUS
EFIAPI
SetOemFwUpdateSignal( VOID )
{
  EFI_STATUS  Status;
 
  // create an event, when this envent is signaled, a verification funcion will be registered.
  Status = gBS->CreateEventEx ( EVT_NOTIFY_SIGNAL,
                                TPL_CALLBACK,
                                SecBootDummyHandler,
                                NULL,
                               &gQcomOemFwUpdateEventGuid,
                               &OemFwUpdateEvent1);
  EXIT_IF_TRUE( Status );

  Status = gBS->SignalEvent(OemFwUpdateEvent1 );
  EXIT_IF_TRUE( Status );

  Status = gBS->CloseEvent( OemFwUpdateEvent1);
  EXIT_IF_TRUE( Status );

ErrorExit:
  return Status;

}

