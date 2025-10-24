
/*===========================================================================

FILE:      GPIOSvcDevice.c

DESCRIPTION:
This file contains the hardware abstraction for the micro GPIO driver.
This file provides the public class implementation of the GPIO driver.

PUBLIC CLASSES:
  TLMM_SvcDeviceInit
  TLMM_SvcDeviceGetGpioId

===========================================================================
Copyright (c) 2017,2021 QUALCOMM Technologies Incorporated.
All Rights Reserved.
QUALCOMM Proprietary/GTDR
========================================================================================================*/

/*========================================================================================================

  EDIT HISTORY FOR FILE

  This section contains comments describing changes made to this file.
  Notice that changes are listed in reverse chronological order.

  $Header: //components/rel/core.boot/6.1.1/QcomPkg/SocPkg/Library/TLMMHWLib/image/common/GPIOSvcDevice.c#1 $

  when       who     what, where, why
  --------   ---     -------------------------------------------------------------------------------------
  06/02/17   dcf     Created.
  ======================================================================================================*/

#include "com_dtypes.h"
#include "GPIOSvcDevice.h"
#include "GPIOTypes.h"
#include "GPIOIFace.h"
#include "GPIOCore.h"
#include "GPIODevCfg.h"
#include "GPIOSvcSync.h"
#include "HALtlmm.h"
#include "HALhwio.h"

/*
 * Array of registered GPIO pins.
 */
extern GPIOPinInfoType ganGpioAccess[];

extern boolean GPIO_IsBlockDescSupported
(
  uint32 nHWVersion
);


/*========================================================================================================

 FUNCTION    GPIO_IsPinInUse

========================================================================================================*/


boolean GPIO_IsPinInUse
(
  uint32 nPin
)
{
  uint32 nIdx = 0;
  
  for (nIdx = 0; nIdx < GPIO_MAX_ARR_SIZE; nIdx++ )
  {
    if ( ganGpioAccess[nIdx].nPin == nPin )
    {
      return TRUE;
    }
  }
  
  return FALSE;
}

boolean GPIO_SvcDeviceInit
(
  HALgpioBlockDescType *pDesc,
  uint32_t             *pSleepArr
)
{
  uint32 nPin = 0;
  uint32 nTotalPins = 0;
  GPIOConfigType PinCfg;
  GPIOValueType eValue = GPIO_LOW;
  uint32 nTileIdx = 0;
  uint32 nBaseOffs = 0;

  if (pSleepArr != NULL && pDesc != NULL)
  {   

    nTotalPins = (pDesc->nMaxPinNumber - pDesc->nMinPinNumber) + 1;

    /*
     * For each GPIO pin, decode the configuration settings and set the low-power register
     * as well as configure the pin to low-power if marked as such and not in use.
     */
    for (nPin = 0; nPin < nTotalPins; nPin++)
    {
      nTileIdx = HAL_tlmm_GetTileIndex(pDesc, nPin);
      nBaseOffs = pDesc->aTiles[nTileIdx];
      eValue = GPIO_LOW;

      PinCfg.func = 0;
      PinCfg.drive = 0;
        
      /*
       * Decode the direction value.
       */
      if (pSleepArr[nPin] & PIN_OUTPUT)
      {
        PinCfg.dir = GPIO_OUT;
          
        /*
         * Check the required output value for the pin.
         */
        if ( pSleepArr[nPin] & PIN_OUT_HIGH )
        {
          eValue = GPIO_HIGH;
        }
      }
      else
      {
        PinCfg.dir = GPIO_IN;
      }
        
      /*
       * Decode the pull value.
       */
      if ( pSleepArr[nPin] & PIN_PULL_DOWN )
      {
        PinCfg.pull = GPIO_PD;
      }
      else if ( pSleepArr[nPin] & PIN_PULL_UP )
      {
        PinCfg.pull = GPIO_PU;
      }
      else if ( pSleepArr[nPin] & PIN_KEEPER )
      {
        PinCfg.pull = GPIO_KP;
      }
      else
      {
        PinCfg.pull = GPIO_NP;
      }

      /*
       * If this GPIO pin has been marked to initialized to low-power
       * do so here.
       */
      if ( pSleepArr[nPin] & PIN_PRG_YES )
      {
        if ( GPIO_IsPinInUse(nPin) == FALSE )
        {
          if ( PinCfg.dir == GPIO_OUT )
          {
            HAL_tlmm_WritePin(pDesc, nBaseOffs, nPin, eValue);
          }
          HAL_tlmm_ConfigPin(pDesc, nBaseOffs, nPin, PinCfg);
        }
      }
      HAL_tlmm_SetInactiveConfig(pDesc, nBaseOffs, nPin, PinCfg, eValue);
    }
  }

  return TRUE;

}


boolean GPIO_RouterInit(void) { return TRUE; }
