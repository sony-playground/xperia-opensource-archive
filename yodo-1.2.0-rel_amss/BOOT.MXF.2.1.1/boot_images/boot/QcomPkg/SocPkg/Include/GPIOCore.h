#ifndef __GPIOCORE_H__
#define __GPIOCORE_H__
/*==========================================================================

FILE:      GPIOCore.c

DESCRIPTION:
  This file contains internal type definitions of the GPIO Core driver.


============================================================================
Copyright (c) 2017,2021 QUALCOMM Technologies Incorporated.
All Rights Reserved.
QUALCOMM Proprietary/GTDR
==========================================================================*/

/*==========================================================================

  EDIT HISTORY FOR FILE

  This section contains comments describing changes made to this file.
  Notice that changes are listed in reverse chronological order.

  $Header: //components/rel/core.boot/6.1.1/QcomPkg/SocPkg/Include/GPIOCore.h#1 $

  when       who     what, where, why
  --------   ---     -------------------------------------------------------
  05/10/21   ara     Updating pin info structure. 
  03/02/17   dcf     Created.
  ========================================================================*/

/*==========================================================================

  INCLUDE FILES FOR MODULE

  ========================================================================*/

#include "GPIOTypes.h"
#include "HALtlmm.h"


/*==========================================================================

                 INTERNAL MACROS AND DATA STRUCTURES

  ========================================================================*/


/*
 * Static array size for GPIO access information.  This array is a subset of
 * the total pins.  If exhausted, the size must be increased at a multiple of
 * 2^n to ensure sizing requirements with the GPIOPinInfo.Info.PinIdx field.
 * The GPIOPinInfo.Info.PinIdx field must also be expanded to account for the
 * increase such that the PinIdx field will not be able to be larger than the
 * total elements in the array.
 */
#define GPIO_MAX_ARR_SIZE  48

/*
 * GPIO Device tree key macros
 * 0 - 7 --> index
 * 16 - 19 --> length
 * 30 - 31 --> type
 */
#define GPIO_MAKE_KEY(category, index, len) \
   (len << 16 | index | category << 30)
#define GPIO_KEY_GET_INDEX(val) \
  (val & 0xFF)
#define GPIO_KEY_GET_LEN(val) \
  (val >> 16 & 0xF)
#define GPIO_KEY_GET_CATEGORY(val) \
  (val >> 30)
  
#define GPIO_ID_CATEGORY_BITBANG 1
#define GPIO_ID_CATEGORY_PINCTRL 2


/*==========================================================================

                     INTERNAL DATA STRUCTURES

  =========================================================================*/

/*
 * GPIO Pin information structure.
 *
 * This structure describes the details for accessing TLMM HW as well as
 * validating information pertaining to the usage and accessibility of a
 * GPIO pin.
 */
typedef struct _GPIOPinInfoType
{
  uint32 nFunc     : 4;   /* Function Select Value */
  uint32 nDir      : 1;   /* Direction Value */
  uint32 nPull     : 2;   /* pull Value      */
  uint32 nDrive    : 11;   /* drive Value     */
  uint32 nPin      : 8;   /* Pin number      */
  uint32 nDeviceId : 2;   /* device ID       */
  uint32 nAccess   : 1;   /* shared/exclusive */
  uint32 nDescIdx  : 2;   /* Index of the hardware descriptor structure */
  uint32 nInUse    : 1;   /* slot in use or not */
}GPIOPinInfoType;


/*=======================================================================================================

  FUNCTION      GPIO_IsPinValid

  DESCRIPTION   Checks the bounds of a GPIO pin based on the supplied HW block descriptor.

  =====================================================================================================*/

boolean GPIO_IsPinValid
(
  HALgpioBlockDescType* pBlock,
  uint32                PinNumber
);


#endif /* __GPIOCORE_H__ */
