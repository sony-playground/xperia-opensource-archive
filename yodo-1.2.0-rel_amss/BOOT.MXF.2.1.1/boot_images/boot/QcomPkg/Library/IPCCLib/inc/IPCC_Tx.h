#ifndef __IPCCTX_H__
#define __IPCCTX_H__
/*
===========================================================================
*/
/**
  @file IPCCTx.h
  @brief Private interface include file for accessing the IPCC Tx
  device driver definitions.

  The IPCCTx.h file is the private API interface to the Inter-Processor 
  Communication Controller driver.
*/
/*
  ===========================================================================

  Copyright (c) 2018-2020 Qualcomm Technologies Incorporated.  
  All Rights Reserved.
  Qualcomm Proprietary and Confidential.

  ===========================================================================

  $Header: //components/rel/core.boot/6.1.1/QcomPkg/Library/IPCCLib/inc/IPCC_Tx.h#1 $
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
#include <stdint.h>

/*=========================================================================
      Interface Declarations
==========================================================================*/


/* =========================================================================
**  Function : IPCCTx_Init
** =========================================================================*/

void
IPCCTx_Init
(
   IPCCDrvCtxt* pDrv
);

/* =========================================================================
**  Function : IPCCTx_Attach
** =========================================================================*/

void
IPCCTx_Attach
(
  IPCCTxDrvInfoType**  ppTxDrv
);

/* =========================================================================
**  Function : IPCCTx_Detach
** =========================================================================*/

void
IPCCTx_Detach
(
  IPCCTxDrvInfoType**  ppTxDrv
);

/* =========================================================================
**  Function : IPCCTx_Trigger
** =========================================================================*/

IPCCErr
IPCCTx_Trigger
(
  IPCCClientCtxt*   pClientCtxt,
  IPCC_Client       eClient,
  IPCC_Signal       nSignalLow,
  IPCC_Signal       nSignalHigh
);

#endif /*__IPCCTX_H__*/
