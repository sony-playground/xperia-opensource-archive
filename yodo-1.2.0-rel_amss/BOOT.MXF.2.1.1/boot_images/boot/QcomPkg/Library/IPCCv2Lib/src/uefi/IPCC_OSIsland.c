/*
===========================================================================
*/
/**
  @file IPCC_OSUEFI.c

  IPC Controller driver Operating system abstraction for UEFI.
*/
/*
  ====================================================================

  Copyright (c) 2020 Qualcomm Technologies Incorporated.
  All Rights Reserved.
  QUALCOMM Proprietary and Confidential.

  ====================================================================

  $Header: //components/dev/core.boot/6.1/shantonu.core.boot.6.1.ipccHwMemOpt_uefi/QcomPkg/Library/IPCCLib/src/uefi/IPCC_OSUEFIIsland.c#1 $
  $DateTime: 2022/06/08 16:30:11 $
  $Author: shantonu $

  ====================================================================
*/


/*=========================================================================
      Include Files
==========================================================================*/
#include "IPCC_OS.h"
#include "HALhwio.h"
#include <stdbool.h>
#include <Library/KernelLib.h>
#include <Library/QcomLib.h>
#include <Uefi.h>
#include <Library/BaseMemoryLib.h>
#include <Library/DebugLib.h>
#include <Library/UefiBootServicesTableLib.h>

/*=========================================================================
      Static definitions
==========================================================================*/


/*=========================================================================
      Functions
==========================================================================*/


/* =========================================================================
**  Function : IPCCOS_Malloc
** =========================================================================*/

void*
IPCCOS_Malloc
(
   uintptr_t nSize
)
{
  void *pMem;
  EFI_STATUS efiStatus;
  efiStatus = gBS->AllocatePool( EfiBootServicesData, nSize, &pMem );
  return (EFI_SUCCESS == efiStatus)? pMem: NULL;
}


/* =========================================================================
**  Function : IPCCOS_Free
** =========================================================================*/

void
IPCCOS_Free
(
   void* p
)
{
  gBS->FreePool( p );
}


/* =========================================================================
**  Function : IPCCOS_Read
** =========================================================================*/

uintptr_t
IPCCOS_Read
(
   uintptr_t nAddress
)
{
  uintptr_t nData;
  nData = in_dword(nAddress);
  return nData;
}


/* =========================================================================
**  Function : IPCCOS_Write
** =========================================================================*/

void
IPCCOS_Write
(
   uintptr_t nAddress,
   uintptr_t nData
)
{
  out_dword(nAddress, nData);
}


/* =========================================================================
**  Function : IPCCOS_Callback
** =========================================================================*/

void
IPCCOS_Callback
(
   IPCC_CB pfnCB,
   IPCC_CBData nData,
   IPCC_Client nClient,
   IPCC_Signal nSignal
)
{
   pfnCB(nData, nClient, nSignal);
}


/* =========================================================================
**  Function : IPCCOS_CallbackExt
** =========================================================================*/

void
IPCCOS_CallbackExt
(
   IPCC_CB          pfnCB,
   IPCC_CBData      nData,
   IPCC_Client      nClient,
   IPCC_Signal      nSignal,
   bool             bIsland
)
{
  IPCCOS_Callback(pfnCB, nData, nClient, nSignal); 
}


