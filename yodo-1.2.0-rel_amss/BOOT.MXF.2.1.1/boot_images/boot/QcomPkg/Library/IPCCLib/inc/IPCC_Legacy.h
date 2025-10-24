#ifndef __IPCCLEGACY_H__
#define __IPCCLEGACY_H__
/*
===========================================================================
*/
/**
  @file IPCCLegacy.h
  @brief Private interface include file for accessing the IPCC legacy
  device driver definitions.

  The IPCCLegacy.h file is the private API interface to the Inter-Processor 
  Communication Controller driver.
*/
/*
  ===========================================================================

  Copyright (c) 2018-2020 Qualcomm Technologies Incorporated.  
  All Rights Reserved.
  Qualcomm Proprietary and Confidential.

  ===========================================================================

  $Header: //components/rel/core.boot/6.1.1/QcomPkg/Library/IPCCLib/inc/IPCC_Legacy.h#1 $
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
      Interface Declarations
==========================================================================*/


/* =========================================================================
**  Function : IPCCLegacy_Init
** =========================================================================*/

void
IPCCLegacy_Init
(
   void
);


/* =========================================================================
**  Function : IPCCLegacy_Attach
** =========================================================================*/

void
IPCCLegacy_Attach
(
  IPCCClientCtxt*   pClientCtxt
);


/* =========================================================================
**  Function : IPCCLegacy_Detach
** =========================================================================*/

void
IPCCLegacy_Detach
(
  IPCCClientCtxt*   pClientCtxt
);


/* =========================================================================
**  Function : IPCCLegacy_RegisterInterrupt
** =========================================================================*/

IPCCErr 
IPCCLegacy_RegisterInterrupt
(
  IPCCClientCtxt*   pClientCtxt,
  IPCC_Client       eSenderCID, 
  IPCC_Signal       nSignalLow,
  IPCC_Signal       nSignalHigh,
  IPCC_CB           pfnCB,
  IPCC_CBData       nData
);


/* =========================================================================
**  Function : IPCCLegacy_DeregisterInterrupt
** =========================================================================*/

IPCCErr 
IPCCLegacy_DeregisterInterrupt
(
  IPCCClientCtxt*   pClientCtxt,
  IPCC_Client       eSenderCID, 
  IPCC_Signal       nSignalLow,
  IPCC_Signal       nSignalHigh
);


/* =========================================================================
**  Function : IPCCLegacy_Trigger
** =========================================================================*/

IPCCErr
IPCCLegacy_Trigger
(
  IPCCClientCtxt*   pClientCtxt,
  IPCC_Client       eTargetCID,
  IPCC_Signal       nSignalLow,
  IPCC_Signal       nSignalHigh
);


/* =========================================================================
**  Function : IPCCLegacy_EnableInterrupt
** =========================================================================*/

IPCCErr
IPCCLegacy_EnableInterrupt
(
  IPCCClientCtxt*   pClientCtxt,
  IPCC_Client       eTargetCID,
  IPCC_Signal       nSignalLow,
  IPCC_Signal       nSignalHigh
);

/* =========================================================================
**  Function : IPCCLegacy_DisableInterrupt
** =========================================================================*/

IPCCErr
IPCCLegacy_DisableInterrupt
(
  IPCCClientCtxt*   pClientCtxt,
  IPCC_Client       eTargetCID,
  IPCC_Signal       nSignalLow,
  IPCC_Signal       nSignalHigh
);

/* =========================================================================
**  Function : IPCC_LegacyIsr
** =========================================================================*/

void
IPCC_LegacyIsr
(
  uint32_t nDataIn
);

#endif /*__IPCCLEGACY_H__*/
