#ifndef __IPCC_OS_H__
#define __IPCC_OS_H__
/*
===========================================================================
*/
/**
  @file IPCC_OS.h
  @brief Private interface include file for accessing the IPCC internal
  Operating system abstraction layer.
*/
/*
  ===========================================================================

  Copyright (c) 2018-2020 Qualcomm Technologies Incorporated.  
  All Rights Reserved.
  Qualcomm Proprietary and Confidential.

  ===========================================================================

  $Header: //components/rel/core.boot/6.1.1/QcomPkg/Library/IPCCLib/inc/IPCC_OS.h#1 $
  $DateTime: 2022/08/18 10:15:46 $
  $Author: pwbldsvc $

  when       who     what, where, why
  --------   ---     ---------------------------------------------------------- 
  07/28/18   cp      Initial revision.

  ===========================================================================
*/


/*=========================================================================
      Include Files
==========================================================================*/

#include "IPCC.h"
#include <stdint.h>
#include <stdbool.h>
#ifdef ARCH_QDSP6
#include "qurt.h"
#endif


/*=========================================================================
      Type Definitions
==========================================================================*/

/**
 * Opaque definition of a mutex
 */
#ifdef ARCH_QDSP6
typedef qurt_mutex_t IPCCOSMutex;
#else
typedef void* IPCCOSMutex;
#endif 


/**
 * Opaque definition of an Interrupt Driver handle
 */
typedef void* IPCCOSInterruptHandle;

/**
 * Definition of Callback handler
 */
typedef void (*IPCCOSCB) (void*);

/**
 * Definition of trigger types for interrupt registration
 */
typedef enum
{
  IPCCOS_TRIGGER_HIGH,
  IPCCOS_TRIGGER_LOW,
  IPCCOS_TRIGGER_RISING,
  IPCCOS_TRIGGER_FALLING
}
IPCCOS_TriggerType;

/*=========================================================================
      Function Definitions
==========================================================================*/

/* =========================================================================
**  Function : IPCCOS_MutexInit
** =========================================================================*/

void 
IPCCOS_MutexInit 
( 
  IPCCOSMutex* pMutex 
);


/* =========================================================================
**  Function : IPCCOS_MutexDeinit
** =========================================================================*/

void 
IPCCOS_MutexDeinit 
( 
  IPCCOSMutex* pMutex 
);


/* =========================================================================
**  Function : IPCCOS_MutexLock
** =========================================================================*/

void 
IPCCOS_MutexLock 
( 
  IPCCOSMutex* pMutex 
);


/* =========================================================================
**  Function : IPCCOS_MutexUnlock
** =========================================================================*/

void 
IPCCOS_MutexUnlock 
( 
  IPCCOSMutex* pMutex 
);


/* =========================================================================
**  Function : IPCCOS_InitInterruptHandle
** =========================================================================*/

IPCCErr
IPCCOS_InitInterruptHandle
(
  IPCCOSInterruptHandle* phInterrupt
);


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
);


/* =========================================================================
**  Function : IPCCOS_DeregisterInterrupt
** =========================================================================*/

IPCCErr
IPCCOS_DeregisterInterrupt
(
  IPCCOSInterruptHandle* phInterrupt,
  uint32_t               nInterrupt
);



/* =========================================================================
**  Function : IPCCOS_EnableInterrupt
** =========================================================================*/

IPCCErr
IPCCOS_EnableInterrupt
(
  IPCCOSInterruptHandle* phInterrupt,
  uint32_t               nInterrupt
);

/* =========================================================================
**  Function : IPCCOS_DisableInterrupt
** =========================================================================*/

IPCCErr
IPCCOS_DisableInterrupt
(
  IPCCOSInterruptHandle* phInterrupt,
  uint32_t               nInterrupt
);

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
);


/* =========================================================================
**  Function : IPCCOS_Malloc
** =========================================================================*/

void*
IPCCOS_Malloc
(
   uintptr_t nSize
);


/* =========================================================================
**  Function : IPCCOS_Free
** =========================================================================*/

void
IPCCOS_Free
(
   void* p
);


/* =========================================================================
**  Function : IPCCOS_Read
** =========================================================================*/

uintptr_t
IPCCOS_Read
(
   uintptr_t nAddress
);


/* =========================================================================
**  Function : IPCCOS_Write
** =========================================================================*/

void
IPCCOS_Write
(
   uintptr_t nAddress,
   uintptr_t nData
);

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
);

/* =========================================================================
**  Function : IPCCOS_CallbackExt
** =========================================================================*/

void
IPCCOS_CallbackExt
(
   IPCC_CB     pfnCB,
   IPCC_CBData nData,
   IPCC_Client nClient,
   IPCC_Signal nSignal,
   bool        bIsland
);

/* =========================================================================
**  Function : IPCCOS_InterruptDone
** =========================================================================*/

IPCCErr
IPCCOS_InterruptDone
(
  IPCCOSInterruptHandle* phInterrupt,
  uint32_t               nInterrupt
);

#endif /*__IPCC_OS_H__*/
