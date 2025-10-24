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

  $Header: //components/rel/core.boot/6.1.1/QcomPkg/Library/IPCCLib/src/uefi/IPCC_OSUEFI.c#1 $
  $DateTime: 2022/08/18 10:15:46 $
  $Author: pwbldsvc $

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


/*=========================================================================
      Static definitions
==========================================================================*/


/*=========================================================================
      Functions
==========================================================================*/


/* =========================================================================
**  Function : IPCCOS_MutexInit
** =========================================================================*/

void 
IPCCOS_MutexInit 
( 
  IPCCOSMutex* pMutex 
)
{
  if( pMutex == NULL ) return;

  //Add snprintf here to enumerate string name
  InitRecursiveLock ("ipcc", (LockHandle**)pMutex);
}


/* =========================================================================
**  Function : IPCCOS_MutexDeinit
** =========================================================================*/

void 
IPCCOS_MutexDeinit 
( 
  IPCCOSMutex* pMutex 
)
{
  if( pMutex == NULL ) return;

  DestroyLock((LockHandle*)*pMutex);
}


/* =========================================================================
**  Function : IPCCOS_MutexLock
** =========================================================================*/

void 
IPCCOS_MutexLock 
( 
  IPCCOSMutex* pMutex 
)
{
  if( pMutex != NULL )
  {
    AcquireLock ((LockHandle*)*pMutex);
  }
}


/* =========================================================================
**  Function : IPCCOS_MutexUnlock
** =========================================================================*/

void 
IPCCOS_MutexUnlock 
( 
  IPCCOSMutex* pMutex 
)
{
  if( pMutex != NULL )
  {
    ReleaseLock ((LockHandle*)*pMutex); 
  }
}


/* =========================================================================
**  Function : IPCCOS_InitInterruptHandle
** =========================================================================*/

IPCCErr
IPCCOS_InitInterruptHandle
(
  IPCCOSInterruptHandle* phInterrupt
)
{
  if( phInterrupt == NULL ) return IPCC_EARG;

  *phInterrupt = (IPCCOSInterruptHandle)0x12345678;

  return IPCC_EOK;
}


/* =========================================================================
**  Function : IPCCOS_RegisterInterrupt
** =========================================================================*/

IPCCErr
IPCCOS_RegisterInterrupt
(
  IPCCOSInterruptHandle* phInterrupt,
  uint32_t               nInterrupt,
  uint32_t               buImage,
  IPCCOS_TriggerType     eTrigger,
  IPCCOSCB               pCB,
  uintptr_t              nArg
)
{
  uint32_t nTrigger;


  if( phInterrupt == NULL ) return IPCC_EARG;

  switch( eTrigger )
  {
    case IPCCOS_TRIGGER_RISING:
    case IPCCOS_TRIGGER_FALLING:
      nTrigger = INTR_CONFIG_EDGE_TRIGGER;
      break;
    case IPCCOS_TRIGGER_HIGH:
    case IPCCOS_TRIGGER_LOW:
    default:
      nTrigger = INTR_CONFIG_LEVEL_TRIGGER;
      break;
  }

  if (RegisterThrCtxtIntrHandler (nInterrupt, (ThrCtxtIntrHandler)pCB, (VOID*)nArg) == EFI_SUCCESS)
    ConfigureInterrupt (nInterrupt, nTrigger, 0);
  UnmaskInterrupt (nInterrupt);

  return IPCC_EOK;
}


/* =========================================================================
**  Function : IPCCOS_DeregisterInterrupt
** =========================================================================*/

IPCCErr
IPCCOS_DeregisterInterrupt
(
  IPCCOSInterruptHandle* phInterrupt,
  uint32_t               nInterrupt
)
{
  MaskInterrupt(nInterrupt);

  return IPCC_EOK;
}


/* =========================================================================
**  Function : IPCCOS_InterruptDone
** =========================================================================*/

IPCCErr
IPCCOS_InterruptDone
(
  IPCCOSInterruptHandle* phInterrupt,
  uint32_t               nInterrupt
)
{
  UnmaskInterrupt(nInterrupt);

  return IPCC_EOK;
}


/* =========================================================================
**  Function : IPCCOS_EnableInterrupt
** =========================================================================*/
 
IPCCErr
IPCCOS_EnableInterrupt
(
  IPCCOSInterruptHandle* phInterrupt,
  uint32_t               nInterrupt
)
{  
  UnmaskInterrupt(nInterrupt);

  return IPCC_EOK;


}
 
/* =========================================================================
**  Function : IPCCOS_DisableInterrupt
** =========================================================================*/
 
IPCCErr
IPCCOS_DisableInterrupt
(
  IPCCOSInterruptHandle* phInterrupt,
  uint32_t               nInterrupt
)
{
  MaskInterrupt(nInterrupt);

  return IPCC_EOK;


}

/* =========================================================================
**  Function : IPCCOS_ErrFatal
** =========================================================================*/

void
IPCCOS_ErrFatal
(
  const char* pszMsg,
  uintptr_t   arg0,
  uintptr_t   arg1,
  uintptr_t   arg2
)
{
  //ERR_FATAL("Error fatal in IPCC driver!", 0, 0, 0);
}



