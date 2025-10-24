/*===========================================================================

FILE:      GPIOCore.c

DESCRIPTION:
This file provides the public class implementation of the GPIO driver.

PUBLIC CLASSES:
  GPIO_Init
  GPIO_Attach
  GPIO_RegisterPinExplicit
  GPIO_ConfigPin
  GPIO_ReadPin
  GPIO_WritePin

===========================================================================
Copyright (c) 2017 QUALCOMM Technologies Incorporated.
All Rights Reserved.
QUALCOMM Proprietary/GTDR
========================================================================================================*/

/*========================================================================================================

  EDIT HISTORY FOR FILE

  This section contains comments describing changes made to this file.
  Notice that changes are listed in reverse chronological order.

  $Header: //components/rel/core.boot/6.1.1/QcomPkg/SocPkg/Library/TLMMHWLib/src/GPIOCore.c#1 $

  when       who     what, where, why
  --------   ---     -------------------------------------------------------------------------------------
  03/02/17   dcf     Created.
  ======================================================================================================*/

/*=======================================================================================================

  INCLUDE FILES FOR MODULE

  =====================================================================================================*/

#include "GPIO.h"
#include "GPIOTypes.h"
#include "GPIOExt.h"
#include "GPIOCore.h"
#include "HALtlmm.h"
#include "GPIOSvcSync.h"
#include "GPIOIFace.h"
#include "GPIODT.h"


/*=======================================================================================================

                               INTERNAL MACROS AND DATA STRUCTURES

  =====================================================================================================*/


/*
 * Internal array of GPIO information.  The size is a subset of all GPIO to save space as the total
 * number of GPIO pins used on a non-HLOS image is expected to be low.
 */
GPIOPinInfoType ganGpioAccess[GPIO_MAX_ARR_SIZE];


/*
 * GPIO block descriptor Array.  THis may be extracted from device config or compiled into
 * the library binary.  This extern definition usage is expected to change.
 */
extern HALgpioBlockDescType GPIOBlockDescriptors[];

extern uint32 gnNumBlockDescs;

extern boolean GPIO_RouterInit(void);
boolean GPIO_SvcInitChipVersion(uint32 *ChipVersion);

uint32 ChipVersion = 0;

boolean bGpioCoreInitialized = FALSE;


/*=======================================================================================================

                                   INTERNAL DATA STRUCTURES

  =====================================================================================================*/

/*=======================================================================================================

                            APPLICATION PROGRAMMERS INTERFACE FUNCTIONS

  =====================================================================================================*/

  
/*========================================================================================================

 FUNCTION    GPIO_CoreInit

========================================================================================================*/

boolean GPIO_CoreInit
(
  void
)
{
  if ( bGpioCoreInitialized == FALSE )
  {
    /*
     * Initialize the internal chip version variable.
     */
    GPIO_SvcInitChipVersion(&ChipVersion);
    
    /*
     * Initialize the synchronization object, if applicable.
     */
    (void)GPIO_SvcSynInit();

    /*
     * Initialize the router protocol if available.
     */
    if ( GPIO_RouterInit() == FALSE )
    {
      return FALSE;
    }

    bGpioCoreInitialized = TRUE;
  }
  
  return TRUE;
  
} /* GPIO_CoreInit */



/*=======================================================================================================

  FUNCTION      GPIO_Attach

  DESCRIPTION   See GPIO.h

  =====================================================================================================*/

GPIOResult GPIO_Attach
(
  GPIODeviceIdType      eDevice,
  GPIOClientHandleType *pHandle
)
{
  if ( pHandle != NULL )
  {
    pHandle->DeviceId = eDevice;
    return GPIO_SUCCESS;
  }
  return GPIO_ERROR;

} /* GPIO_Init */



/*========================================================================================================

 FUNCTION    GPIO_IsBlockDescSupported

========================================================================================================*/

boolean GPIO_IsBlockDescSupported
(
  uint32 nHWVersion
)
{
  if ( (nHWVersion == 0) || ((GPIO_MIN_TO_CHIPINFO(nHWVersion) <= ChipVersion) && (GPIO_MAX_TO_CHIPINFO(nHWVersion) >= ChipVersion)) )
  {
    return TRUE;
  }
  return FALSE;

}



/*=======================================================================================================

  FUNCTION      GPIO_IsPinValid

  DESCRIPTION   Checks the bounds of a GPIO pin based on the supplied HW block descriptor.

  =====================================================================================================*/

boolean GPIO_IsPinValid
(
  HALgpioBlockDescType* pBlock,
  uint32                PinNumber
)
{
    return (pBlock != NULL && PinNumber >= pBlock->nMinPinNumber && PinNumber <= pBlock->nMaxPinNumber);

} /* END GPIO_IsPinValid */



/*=======================================================================================================

  FUNCTION      GPIO_RegisterPinExplicit

  DESCRIPTION   See GPIO.h

  =====================================================================================================*/

GPIOResult GPIO_RegisterPinExplicit
(
  GPIOClientHandleType  Handle,
  uint32                nGpioNumber,
  GPIOAccessType        AccessType,
  GPIOKeyType          *GPIOKey
)
{
  uint32     nSlotIdx, nDescIdx;
  GPIOResult eStatus = GPIO_SUCCESS;


  if (bGpioCoreInitialized == FALSE)
  {
    GPIO_CoreInit();
  }
  /*
   * Check if there is a current match and if it is specified as shared
   * access.  Return FALSE if it is exclusive.
   */

  GPIO_SyncEnter();

  for ( nSlotIdx = 0; nSlotIdx < GPIO_MAX_ARR_SIZE; nSlotIdx++ )
  {
    /*
     * If we encounter an empty array slot this pin has not been registered yet.
     */
    if ( ganGpioAccess[nSlotIdx].nInUse == 0 )
    {
      break;
    }
    if ( (ganGpioAccess[nSlotIdx].nPin == nGpioNumber) &&
         (ganGpioAccess[nSlotIdx].nDeviceId == Handle.DeviceId) )
    {
      if ( ganGpioAccess[nSlotIdx].nAccess == GPIO_ACCESS_SHARED )
      {
        /*
         * Found a match.  Short circuit and return success.
         */
        *GPIOKey = GPIO_MAKE_KEY(GPIO_ID_CATEGORY_BITBANG, nSlotIdx, 1);
        GPIO_SyncExit();
        return GPIO_SUCCESS;
      }
      else
      {
        eStatus = GPIO_ERROR;
      }
    }
  }

  /*
   * GPIO has not been registered yet.  Hook up the next available spot.
   */
  if ( (nSlotIdx < GPIO_MAX_ARR_SIZE) && (eStatus != GPIO_ERROR) )
  {
    for ( nDescIdx = 0; nDescIdx < gnNumBlockDescs; nDescIdx++ )
    {
      if ( (Handle.DeviceId == GPIOBlockDescriptors[nDescIdx].eDeviceId) &&
         ( (TRUE == GPIO_IsBlockDescSupported(GPIOBlockDescriptors[nDescIdx].nHWVersion))) )
      {
        break;
      }
    }

    /*
     * If the block descriptor was found and the GPIO is valid, we can hook it up.
     */
    if ( nDescIdx < gnNumBlockDescs &&
           GPIO_IsPinValid(&GPIOBlockDescriptors[nDescIdx], nGpioNumber) )
    {
      ganGpioAccess[nSlotIdx].nPin      = nGpioNumber;
      ganGpioAccess[nSlotIdx].nAccess   = AccessType;
      ganGpioAccess[nSlotIdx].nDeviceId = Handle.DeviceId;
      ganGpioAccess[nSlotIdx].nDescIdx  = nDescIdx;
      ganGpioAccess[nSlotIdx].nInUse    = 1;
      *GPIOKey                          = GPIO_MAKE_KEY(GPIO_ID_CATEGORY_BITBANG, nSlotIdx, 1);
      eStatus = GPIO_SUCCESS;
    }
    else
    {
      eStatus = GPIO_ERROR;
    }
  }

  GPIO_SyncExit();

  return eStatus;

} /* GPIO_RegisterPinExplicit */

/*=======================================================================================================

  FUNCTION      GPIO_ConfigPin

  DESCRIPTION   See GPIO.h

  =====================================================================================================*/

GPIOResult GPIO_ConfigPin
(
  GPIOClientHandleType Handle,
  GPIOKeyType          GPIOKey,
  GPIOConfigType       Config
)
{
  HALgpioBlockDescType *pDesc = NULL;
  uint32                nBaseOffs = 0;
  GPIOPinInfoType       PinInfo;
  GPIOResult            eResult = GPIO_ERROR;

  /*
   * Synchronize access.
   */
  GPIO_SyncEnter();

  if ( GPIO_KEY_GET_CATEGORY(GPIOKey) == GPIO_ID_CATEGORY_BITBANG && GPIO_KEY_GET_INDEX(GPIOKey) < GPIO_MAX_ARR_SIZE) 
  {
    PinInfo = ganGpioAccess[GPIO_KEY_GET_INDEX(GPIOKey)];
    pDesc = &GPIOBlockDescriptors[PinInfo.nDescIdx];

    /*
     * Get the offset from the base address and program the GPIO.
     */
    nBaseOffs = pDesc->aTiles[0];
    HAL_tlmm_ConfigPin(pDesc, nBaseOffs, PinInfo.nPin, Config);
    /* Update active config in local memory */
    PinInfo.nDir = Config.dir;
    PinInfo.nPull = Config.pull;
    PinInfo.nDrive = Config.drive;
    PinInfo.nFunc = Config.func;
    eResult = GPIO_SUCCESS;
  }
  else if (GPIO_KEY_GET_CATEGORY(GPIOKey) == GPIO_ID_CATEGORY_PINCTRL)
  {
    eResult = GPIO_ConfigPinctrl(Handle, GPIOKey);
  }

  GPIO_SyncExit();

  return eResult;

} /* END GPIO_ConfigPin */



/*=======================================================================================================

  FUNCTION      GPIO_ReadPin

  DESCRIPTION   See GPIO.h

  =====================================================================================================*/

GPIOResult GPIO_ReadPin
(
  GPIOClientHandleType Handle,
  GPIOKeyType          GPIOKey,
  GPIOValueType       *pValue
)
{
  HALgpioBlockDescType* pDesc = NULL;
  GPIOPinInfoType PinInfo;
  uint32 nBaseOffs = 0;

  if (pValue != NULL && GPIO_KEY_GET_CATEGORY(GPIOKey) == GPIO_ID_CATEGORY_BITBANG && GPIO_KEY_GET_INDEX(GPIOKey) < GPIO_MAX_ARR_SIZE)
  {
    PinInfo = ganGpioAccess[GPIO_KEY_GET_INDEX(GPIOKey)];
    /*
     * Get the block descriptor for this GPIO.
     */
    pDesc = &GPIOBlockDescriptors[PinInfo.nDescIdx];
    nBaseOffs = pDesc->aTiles[0];
    
    *pValue = HAL_tlmm_ReadPin(pDesc, nBaseOffs, PinInfo.nPin);
    return GPIO_SUCCESS;
  }
  return GPIO_ERROR;  

} /* GPIO_ReadPin */



/*=======================================================================================================

  FUNCTION      GPIO_WritePin

  DESCRIPTION   See GPIO.h

  =====================================================================================================*/

GPIOResult GPIO_WritePin
(
  GPIOClientHandleType Handle,
  GPIOKeyType          GPIOKey,
  GPIOValueType        eValue
)
{
  HALgpioBlockDescType* pDesc = NULL;
  GPIOPinInfoType PinInfo;
  uint32 nBaseOffs = 0;

  if ( GPIO_KEY_GET_CATEGORY(GPIOKey) == GPIO_ID_CATEGORY_BITBANG && GPIO_KEY_GET_INDEX(GPIOKey) < GPIO_MAX_ARR_SIZE)
  {
    PinInfo = ganGpioAccess[GPIO_KEY_GET_INDEX(GPIOKey)];
    /*
     * Synchronize access.
     */
    GPIO_SyncEnter();

    pDesc = &GPIOBlockDescriptors[PinInfo.nDescIdx];
    nBaseOffs = pDesc->aTiles[0];
    HAL_tlmm_WritePin(pDesc, nBaseOffs, PinInfo.nPin, eValue);

    GPIO_SyncExit();

    return GPIO_SUCCESS;
  }
  return GPIO_ERROR;

} /* GPIO_WritePin */


