#ifndef __IPCC_INFO_H__
#define __IPCC_INFO_H__
/*
===========================================================================
*/
/**
  @file IPCC_Info.h
  @brief Restricted interface include file for accessing the IPCC
  device driver info.

  The IPCC_Info.h file is a restricted API interface to the Inter-Processor 
  Communication Controller driver.
*/
/*
  ===========================================================================

  Copyright (c) 2019-2020 Qualcomm Technologies Incorporated.  
  All Rights Reserved.
  Qualcomm Proprietary and Confidential.

  ===========================================================================

  $Header: //components/rel/core.boot/6.1.1/QcomPkg/Library/IPCCLib/api/IPCC_Info.h#1 $
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

#include "IPCC.h"
#include <stdint.h>


/*=========================================================================
      Interface Declarations
==========================================================================*/


/* =========================================================================
**  Function : IPCC_GetTriggerAddressAndData
** =========================================================================*/
/**
  Gets the physical address and value to write for a given client to generate
  an interrupt on the given signal to the local subsystem.

  @param
  h[in]          - Client handle.
  eSenderCID[in] - Client ID of the sender.
  nSignal[in]    - Signal value to trigger on to the local client.
  pa[out]        - Physical address of the IPC_SEND register for the sending client.
  nData[out]     - Value to write to generate the interrupt for signal nSignal on
                    the local client.

  @return
  IPCC_EOK   - Success.
  IPCC_EARG  - Error with one of the arguments passed in.

  @dependencies
  None.
*/

IPCCErr
IPCC_GetTriggerAddressAndData
(
  IPCC_Handle   h,
  IPCC_Client   eSenderCID,
  IPCC_Signal   nSignal,
  uintptr_t    *pa,
  uint32_t     *nData
); 

#endif /*__IPCC_INFO_H__*/
