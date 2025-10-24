#ifndef __IPCCRX_H__
#define __IPCCRX_H__
/*
===========================================================================
*/
/**
  @file IPCCRx.h
  @brief Private interface include file for accessing the IPCC Rx
  device driver definitions.

  The IPCCRx.h file is the private API interface to the Inter-Processor 
  Communication Controller driver.
*/
/*
  ===========================================================================

  Copyright (c) 2018-2020 Qualcomm Technologies Incorporated.  
  All Rights Reserved.
  Qualcomm Proprietary and Confidential.

  ===========================================================================

  $Header: //components/rel/core.boot/6.1.1/QcomPkg/Library/IPCCLib/inc/IPCC_Rx.h#1 $
  $DateTime: 2022/08/18 10:15:46 $
  $Author: pwbldsvc $

  when       who     what, where, why
  --------   ---     ---------------------------------------------------------- 
  05/18/18   cp      Initial revision.

  ===========================================================================
*/


/*=========================================================================
      Include Files
==========================================================================*/

#include "IPCC.h"
#include "IPCC_Internal.h"
#include "IPCC_OS.h"
#include <stdint.h>

/*=========================================================================
      Macro Declarations
==========================================================================*/

#define IPCC_NO_DATA 0xffffffff

/*=========================================================================
      Interface Declarations
==========================================================================*/


/* =========================================================================
**  Function : IPCCRx_Init
** =========================================================================*/

void
IPCCRx_Init
(
   IPCCDrvCtxt* pDrv
);


/* =========================================================================
**  Function : IPCCRx_Attach
** =========================================================================*/

void
IPCCRx_Attach
(
  IPCCClientCtxt*   pClientCtxt
);


/* =========================================================================
**  Function : IPCCRx_Detach
** =========================================================================*/

void
IPCCRx_Detach
(
  IPCCClientCtxt*   pClientCtxt
);


/* =========================================================================
**  Function : IPCC_RxIsr
** =========================================================================*/

void
IPCC_RxIsr
(
  uintptr_t nArg
);


/* =========================================================================
**  Function : IPCCRx_RegisterInterrupt
** =========================================================================*/

IPCCErr 
IPCCRx_RegisterInterrupt
(
  IPCCClientCtxt*   pClientCtxt,
  IPCC_Client       eCID, 
  IPCC_Signal       nSignalLow,
  IPCC_Signal       nSignalHigh,
  IPCC_CB           pfnCB,
  IPCC_CBData       nData
);


/* =========================================================================
**  Function : IPCCRx_DeregisterInterrupt
** =========================================================================*/

IPCCErr 
IPCCRx_DeregisterInterrupt
(
  IPCCClientCtxt*   pClientCtxt,
  IPCC_Client       eCID, 
  IPCC_Signal       nSignalLow,
  IPCC_Signal       nSignalHigh
);





/* =========================================================================
**  Function : IPCCRx_EnableInterrupt
** =========================================================================*/

IPCCErr 
IPCCRx_EnableInterrupt
(
  IPCCClientCtxt*   pClientCtxt,
  IPCC_Client       eCID, 
  IPCC_Signal       nSignalLow,
  IPCC_Signal       nSignalHigh
);


/* =========================================================================
**  Function : IPCCRx_DisableInterrupt
** =========================================================================*/

IPCCErr 
IPCCRx_DisableInterrupt
(
  IPCCClientCtxt*   pClientCtxt,
  IPCC_Client       eCID, 
  IPCC_Signal       nSignalLow,
  IPCC_Signal       nSignalHigh
);

/* =========================================================================
**  Function : IPCCRx_GetConfig
** =========================================================================*/

IPCCErr 
IPCCRx_GetConfig
(
  IPCCClientCtxt*   pClientCtxt,
  IPCC_Client       eCID, 
  IPCC_Signal       nSignalLow,
  IPCC_Signal       nSignalHigh,
  IPCC_ConfigType   eConfigType,
  uint32_t*         pnValue
);

/* =========================================================================
**  Function : IPCC_SetConfig
** =========================================================================*/

IPCCErr 
IPCCRx_SetConfig
(
  IPCCClientCtxt*   pClientCtxt,
  IPCC_Client       eCID, 
  IPCC_Signal       nSignalLow,
  IPCC_Signal       nSignalHigh,
  IPCC_ConfigType   eConfigType,
  uint32_t          nValue
);


#endif /*__IPCCRX_H__*/


