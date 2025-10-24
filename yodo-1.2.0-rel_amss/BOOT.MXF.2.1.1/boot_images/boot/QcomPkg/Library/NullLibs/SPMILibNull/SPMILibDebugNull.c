/** @file SPMILibNull.c
  
  Stub functions for SPMIDebugLib

  Copyright (c) 2015-2018, 2021, Qualcomm Technologies, Inc. All 
  rights reserved. 
**/

/*=============================================================================
                              EDIT HISTORY


 when       who     what, where, why
 --------   ---     -----------------------------------------------------------
06/20/16    kpa     Added SpmiBusCfg_Init
05/08/15    plc     Initial revision

=============================================================================*/


/*==========================================================================

                               INCLUDE FILES

===========================================================================*/
#include <Uefi.h>
#include <Library/DebugLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Protocol/EFISPMI.h>
#include "SpmiBus.h"

/*===========================================================================
                      FUNCTION DECLARATIONS
===========================================================================*/ 

Spmi_Result SpmiBusDebug_Init()
{
    return SPMI_SUCCESS;
}


Spmi_Result SpmiBus_ReadLongDebug(uint32 vSlaveId,
                                  Spmi_AccessPriority priority,
                                  uint32 address,
                                  uint8* data,
                                  uint32 len,
                                  uint32* bytesRead)
{
    return SPMI_SUCCESS;
}


Spmi_Result SpmiBus_WriteLongDebug(uint32 vSlaveId,
                                   Spmi_AccessPriority priority,
                                   uint32 address,
                                   uint8* data,
                                   uint32 len)
{
    return SPMI_SUCCESS;
}


Spmi_Result SpmiBus_ReadModifyWriteLongByteDebug(uint32 vSlaveId,
                                                 Spmi_AccessPriority priority,
                                                 uint32 address,
                                                 uint8 data,
                                                 uint8 mask,
                                                 uint8 *byteWritten)
{
    return SPMI_SUCCESS;
}


Spmi_Result SpmiBus_VerifyDebugMode()
{
    return SPMI_SUCCESS;
}

