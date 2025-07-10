#ifndef __OEMPLATFORMLIB_H__
#define __OEMPLATFORMLIB_H__
/*=============================================================================
 
  File: OEMPlatformLib.h
 
 OEM platforms specific
=============================================================================*/

/**
  Copyright (c) 2021, Qualcomm Technologies, Inc. All rights reserved.
**/

/*=============================================================================
                              EDIT HISTORY


 when       who     what, where, why
 --------   ---     -----------------------------------------------------------
 08/16/21   ck      Added edit history and copyright

=============================================================================*/

/*===========================================================================

                     INCLUDE FILES FOR MODULE

===========================================================================*/
#include "MDPTypes.h"
#include "MDPPlatformLib.h"


/*===========================================================================
                        Defines and Structs
===========================================================================*/

/*===========================================================================

                        Public Functions

===========================================================================*/

/* MDP platform specific configuration function 
 */
MDP_Status OEMPlatformConfigure(MDP_Display_IDType eDisplayId, MDPPlatformConfigType eConfig, MDPPlatformParams *pPlatformParams);


#endif // __OEMPLATFORMLIB_H__


