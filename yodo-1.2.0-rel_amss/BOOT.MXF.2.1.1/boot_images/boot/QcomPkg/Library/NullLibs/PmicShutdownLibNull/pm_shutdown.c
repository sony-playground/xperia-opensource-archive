/*===========================================================================
                        PMIC SHUTDOWN PROTOCOL
   DESCRIPTION
   This file contains functions prototypes and variable/type/constant
   declarations for supporting Shutdown Services for the Qualcomm 
   PMIC chip set.


   Copyright (c) 2015-2017 Qualcomm Technologies, Inc.  All Rights Reserved.
   Qualcomm Technologies Proprietary and Confidential.

===========================================================================*/
/*===========================================================================

                        EDIT HISTORY FOR MODULE

  This section contains comments describing changes made to the module.
  Notice that changes are listed in reverse chronological order.


$Header: //components/rel/core.boot/6.1.1/QcomPkg/Library/NullLibs/PmicShutdownLibNull/pm_shutdown.c#1 $
$Author: pwbldsvc $
$DateTime: 2022/08/18 10:15:46 $
when       who     what, where, why
--------   ---     ---------------------------------------------------------- 
09/16/15   al      Porting latest
===========================================================================*/
/*===========================================================================
                     INCLUDE FILES FOR MODULE
===========================================================================*/
#include "PmicShutdown.h"
#include <Uefi.h>

/*===========================================================================
                  FUNCTION DEFINITIONS
===========================================================================*/

/*===========================================================================
FUNCTION PmicShutdown                                EXTERNAL FUNCTION  
DESCRIPTION
    This function disables SMPL bit and writes normal shutdown to PS_HOLD_RESET_CTL register. With these features 
  disabled, PMIC shuts off if PS_HOLD pin goes low.

  EXAMPLE:
  // shutdown the PMIC. 
  EFI_STATUS Status = PmicShutdown();

  // Was shutdown successful? 
  if (EFI_SUCCESS == Status) 
  {
    //Pull down PS_HOLD
  }

RETURN VALUE
  Return value type: EFI_STATUS.
    - EFI_SUCCESS  = PS_HOLD is ready to be pulled down
    - EFI_DEVICE_ERROR = Shutdown failed to disable the WDOG and SMPL bits.
===========================================================================*/
EFI_STATUS
EFIAPI
PmicShutdown()
{
    return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
PmicHardReset()
{
    return EFI_SUCCESS;
}


EFI_STATUS
EFIAPI
PmicReset(pm_pon_reset_cfg_type Reset)
{
   return EFI_SUCCESS;
}


