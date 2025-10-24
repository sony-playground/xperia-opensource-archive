#ifndef __IPCC_IMAGE_H__
#define __IPCC_IMAGE_H__
/*
===========================================================================
*/
/**
  @file IPCCImage.h
  @brief Private interface include file for accessing the IPCC image specific
  device driver.

  The IPCCImage.h file is the private API interface to the Inter-Processor 
  Communication Controller driver.
*/
/*
  ===========================================================================

  Copyright (c) 2018-2020 Qualcomm Technologies Incorporated.  
  All Rights Reserved.
  Qualcomm Proprietary and Confidential.

  ===========================================================================

  $Header: //components/rel/core.boot/6.1.1/QcomPkg/Library/IPCCLib/inc/IPCC_Image.h#1 $
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

#include "IPCC_Internal.h"
#include <stdint.h>


/*=========================================================================
      Interface Declarations
==========================================================================*/


/* =========================================================================
**  Function : IPCC_InitImage
** =========================================================================*/
/**
  Initialize the IPCC image specific portion of the driver.

  This function links up the BSP data to the driver.

  @param
  pDrv - Pointer to driver context.

  @return
  None.

  @dependencies
  None.
*/

void
IPCC_InitImage
(
   IPCCDrvCtxt* pDrv
);

/* =========================================================================
**  Function : IPCC_InitSubsysImage
** =========================================================================*/
/**
  Initialize the IPCC image specific portion of the driver based on the
  subsystem.

  This function will gather subsystem specific information and/or initialize
  IPCC based on the subsystem in use.

  @param
  pDrv - Pointer to driver context.

  @return
  None.

  @dependencies
  None.
*/

void
IPCC_InitSubsysImage
(
   IPCCDrvCtxt* pDrv
);

/* =========================================================================
**  Function : IPCCLegacy_InitImage
** =========================================================================*/
/**
  Initialize the IPCC Legacy image specific portion of the driver.

  This function links up the BSP data to the driver.

  @param
  pDrv - Pointer to driver context.

  @return
  None.

  @dependencies
  None.
*/

void
IPCCLegacy_InitImage
(
   IPCCLegacyDrvCtxt* pDrv
);

/* =========================================================================
**  Function : IPCCLegacy_InitSubsysImage
** =========================================================================*/
/**
  Initialize the Subsystem specific IPCC Legacy image
  specific portion of the driver.

  This function links up the BSP data to the driver.

  @param
  pDrv - Pointer to driver context.

  @return
  None.

  @dependencies
  None.
*/

void
IPCCLegacy_InitSubsysImage
(
   IPCCLegacyDrvCtxt* pDrv
);

#endif /*__IPCC_IMAGE_H__*/
