/*
===========================================================================
*/
/**
  @file IPCCImage.c

  IPC Controller common image driver code.
*/
/*
  ====================================================================

  Copyright (c) 2018-2020 Qualcomm Technologies Incorporated.
  All Rights Reserved.
  QUALCOMM Proprietary and Confidential.

  ====================================================================

  $Header: //components/rel/core.boot/6.1.1/QcomPkg/Library/IPCCLib/image/IPCCImage.c#1 $
  $DateTime: 2022/08/18 10:15:46 $
  $Author: pwbldsvc $

  ====================================================================
*/


/*=========================================================================
      Include Files
==========================================================================*/
#include "IPCC.h"
#include "IPCC_Internal.h"
#include "IPCC_Image.h"
#include <stddef.h>

/*=========================================================================
      External data
==========================================================================*/

extern IPCCBSPDataType        IPCCBSPData;
extern IPCCLegacyBSPDataType  IPCCLegacyBSPData;

/*=========================================================================
      Functions
==========================================================================*/


/* =========================================================================
**  Function : IPCC_InitImage
** =========================================================================*/
/**
  Initialize the IPCC image specific portion of the driver.

  This function links up the BSP data to the driver.

  @param
  None.

  @return
  None.

  @dependencies
  None.
*/

void
IPCC_InitImage
(
  IPCCDrvCtxt* pDrv
)
{
  /* We should never hit this, but do it just incase */
  if ( pDrv == NULL ) return;

  /* Link up BSP data */
  pDrv->pBSP = &IPCCBSPData;

  /* Init subsystem */
  IPCC_InitSubsysImage(pDrv);
}


/* =========================================================================
**  Function : IPCCLegacy_InitImage
** =========================================================================*/
/**
  Initialize the IPCC Legacy image specific portion of the driver.

  This function links up the BSP data to the driver.

  @param
  None.

  @return
  None.

  @dependencies
  None.
*/

void
IPCCLegacy_InitImage
(
  IPCCLegacyDrvCtxt* pLegacyDrv
)
{
  /* We should never hit this, but do it just incase */
  if ( pLegacyDrv == NULL ) return;

  /* Link up BSP data */
  pLegacyDrv->pLegacyBSP = &IPCCLegacyBSPData;

  /* Initialize subsystem specific data */
  IPCCLegacy_InitSubsysImage(pLegacyDrv);
}



