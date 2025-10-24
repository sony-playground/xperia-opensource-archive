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

  Copyright (c) 2019-2020 Qualcomm Technologies Incorporated.  
  All Rights Reserved.
  Qualcomm Proprietary and Confidential.

  ===========================================================================

  $Header: //components/rel/core.boot/6.1.1/QcomPkg/Library/IPCCLib/inc/IPCC_InfoInternal.h#1 $
  $DateTime: 2022/08/18 10:15:46 $
  $Author: pwbldsvc $

  when       who     what, where, why
  --------   ---     ---------------------------------------------------------- 
  01/17/19   cp      Initial revision.

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
