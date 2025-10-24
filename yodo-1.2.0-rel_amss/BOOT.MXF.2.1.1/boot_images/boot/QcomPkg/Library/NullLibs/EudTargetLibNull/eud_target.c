/****************************************************************************

                 Embedded USB Debugger Target Library Routines
                 --------------------------------------

DESCRIPTION
This file contains Public APIs for making use of the EUD HW block.

Copyright (c) 2020 QUALCOMM Technologies Incorporated.
All Rights Reserved. Qualcomm Proprietary

This section contains comments describing changes made to this file.
Notice that changes are listed in reverse chronological order.

$Header: //components/rel/core.boot/6.1.1/QcomPkg/Library/NullLibs/EudTargetLibNull/eud_target.c#1 $

when       who      what, where, why
--------   ---      ----------------------------------------------------------
07/21/20   amcheriy Created.
******************************************************************************/

#include "EUD.h"
#include "eud_config.h"
#include "GPIO.h"
#include "busywait.h"
#include <stdio.h>
#include "boot_logger_if.h"

/*
* @function    EUDReadGPIOState
* @abstract    Read GPIO state to condition EUD enablement.  
* @param       GPIO number and pointer to hold boolean result 
* @result      Enum of type eud_err_type
* @discussion  Perform a GPIO state detection and return result to upper layer
*/
static eud_err_type EUDReadGPIOState(uint32_t nGPIO, boolean *EUDEnable)
{
   eud_err_type err = EUD_ERR_GPIO_CONFIG;
   return err;
}

/*
* @function    EUDTargetEnable
* @abstract    Target specific API Embedded USB Debugger early on in boot stages
* @param       None
* @result      Enum of type eud_err_type
* @discussion  Enabled EUD early on after checking state of a physical GPIO pin
*/
eud_err_type EUDTargetEnable(void)
{
  return EUD_ERR_NONE;
}


