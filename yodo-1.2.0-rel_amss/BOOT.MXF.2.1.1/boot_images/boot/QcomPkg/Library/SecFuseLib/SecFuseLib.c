/*===========================================================================

                              SEC Fuse Lib

GENERAL DESCRIPTION
  This module provides support to sec fuse lib check. 

Copyright 2017,2018,2022 by Qualcomm Technologies, Incorporated.  All Rights Reserved.
===========================================================================*/

/*===========================================================================
                           EDIT HISTORY FOR FILE
  This section contains comments describing changes made to the module.
  Notice that changes are listed in reverse chronological order.

when       who        what, where, why
--------   ---        -------------------------------------------------------
11/19/20   cm         Include TzAsmlib
09/20/18   kpa        Added IsSecFuseLibNull
06/22/17   na         Initial revision.
===========================================================================*/

/*===========================================================================
                     INCLUDE FILES FOR MODULE
===========================================================================*/
#include <scm_sip_interface.h>
#include <Uefi.h>
#include <Library/BaseLib.h>
#include <Library/DebugLib.h>
#include <TzAsmLib.h>

/*===========================================================================
                    VARIABLE DECLARATIONS FOR MODULE
===========================================================================*/

/*===========================================================================
                        LOCAL FUNCTION DEFINITIONS
=============================================================================*/

/*===========================================================================
**  Function :  JTAGDebugDisableFusesBlown
** ==========================================================================
*/
/**
 Check if the debug disable fuses are blown

  @retval TRUE Any of the related DEBUG_DISABLE fuses are blown
  @retval FALSE None of the related DEBUG_DISABLE fuses are blown

**/
BOOLEAN 
EFIAPI
JTAGDebugDisableFusesBlown(void)
{
  INTN          Status;
  UINTN         SecurityState = 0; 
  UINTN         DirectParameters[TZASMLIB_NUM_DIRECT_REQUEST_PARAMETERS] = { 0 };
  UINTN         InternalTrustedOsId;
  
  UINT32 smc_id = TZ_INFO_GET_SECURE_STATE;
  smc_id = (sizeof(UINTN) == 8)?SET_BIT(smc_id, AARCH_BIT):CLR_BIT(smc_id, AARCH_BIT);
  
  Status =  tz_armv8_smc_call(smc_id,
                              TZ_INFO_GET_SECURE_STATE_PARAM_ID,
                              DirectParameters,
                              &InternalTrustedOsId);
  if(Status != 0) 
  {  
    DEBUG((EFI_D_ERROR, "TZ SMC call Failed!\r\n"));
    ASSERT(Status == 0);
    CpuDeadLoop();
    return FALSE;
  }

  SecurityState = DirectParameters[0];
  
  //Check the Bit#2 for debug disable check
  if(!((SecurityState >> 2) & 0x1)) 
  {
    return TRUE; //debug disable check pass, debug disabled
  }

  return FALSE; //debug disable check failed, debug enabled
}

/*===========================================================================
**  Function :  IsSecFuseLibNull
** ==========================================================================
*/
/**
  Check if SecFuseLib is a stub/ Null Lib

  @retval FALSE Actual implementation of SecFuseLib always returns FALSE

**/
BOOLEAN 
EFIAPI
IsSecFuseLibNull(void)
{
  return FALSE; 
}
