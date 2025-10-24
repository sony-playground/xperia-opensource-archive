#ifndef __IPCC_INFOINTERNAL_H__
#define __IPCC_INFOINTERNAL_H__
/*
===========================================================================
*/
/**
  @file IPCC_InfoInternal.h
  @brief Restricted internal interface include file for accessing the IPCC
  device driver info.

  The IPCC_InfoInternal.h file is a restricted API interface to the Inter-Processor 
  Communication Controller driver.
*/
/*
  ===========================================================================

  Copyright (c) 2022 Qualcomm Technologies Incorporated.  
  All Rights Reserved.
  Qualcomm Proprietary and Confidential.

  ===========================================================================

  $Header: $
  $DateTime: $
  $Author: $

  ===========================================================================
*/


/*=========================================================================
      Include Files
==========================================================================*/

#include "IPCC_Internal.h"
#include <stdint.h>


/*=========================================================================
      Interface Declarations
==========================================================================*/


/* =========================================================================
**  Function : IPCCInfo_Init
** =========================================================================*/
/**
  Initialize the IPCC info specific portion of the driver.

  This function links up the BSP data to the driver.

  @param
  pDrv - Pointer to driver context.

  @return
  None.

  @dependencies
  None.
*/

IPCCErr
IPCCInfo_Init
(
   IPCCDrvCtxt* pDrv
); 

#endif /*__IPCC_INFOINTERNAL_H__*/
