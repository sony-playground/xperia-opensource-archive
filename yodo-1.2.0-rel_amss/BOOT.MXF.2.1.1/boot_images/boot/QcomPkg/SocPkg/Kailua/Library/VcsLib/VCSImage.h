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

  Copyright (c) 2021 QUALCOMM Technologies Incorporated.  All Rights Reserved.
  QUALCOMM Proprietary and Confidential. 

  ==================================================================== 
  $Header: //components/rel/core.boot/6.1.1/QcomPkg/SocPkg/Kailua/Library/VcsLib/VCSImage.h#1 $
  $DateTime: 2022/08/18 10:15:46 $
  $Author: pwbldsvc $
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

