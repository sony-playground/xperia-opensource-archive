#ifndef __VCS_IMAGE_H__
#define __VCS_IMAGE_H__
/*
===========================================================================
*/
/**
  @file VCSImage.h
  
*/
/*  
  ====================================================================

  Copyright (c) 2017- 2019 QUALCOMM Technologies Incorporated.  All Rights Reserved.
  QUALCOMM Proprietary and Confidential. 

  ==================================================================== 
  $Header: //components/dev/core.boot/6.0/aravapal.core.boot.6.0.tip_dev/QcomPkg/SocPkg/Clarence/Library/VcsLib/VCSImage.h#1 $
  $DateTime: 2022/04/30 21:50:34 $
  $Author: aravapal $
  ====================================================================
*/ 


/*=========================================================================
      Include Files
==========================================================================*/

#include "Drivers/VcsDxe/VCSDriver.h"



/*=========================================================================
      Macro Definitions
==========================================================================*/


/*=========================================================================
      Type Definitions
==========================================================================*/


/**
 * VCS driver image context.
 */
typedef struct
{
  uint32 nothing;  // this is needed to prevent an empty structure warning.
} VCSImageCtxtType;


/*=========================================================================
      Function Definitions
==========================================================================*/

/* =========================================================================
**  Function : VCS_InitImage
** =========================================================================*/
/**
  Initialize the image specific portion of the driver.

  This function initializes the portion of the driver that is specific
  to the image we are running on and common between chipsets.

  @param *pDrvCtxt [in] -- Handle to the DAL driver context.

  @return
  DAL_SUCCESS -- Init was successful.
  DAL_ERROR -- Initialization failed.

  @dependencies
  None.
*/

DALResult VCS_InitImage
(
  VCSDrvCtxt *pDrvCtxt
);


#endif /* __VCS_IMAGE_H__ */

