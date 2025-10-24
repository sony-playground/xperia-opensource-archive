#ifndef WATCHDOGTIMERLIB_H
#define WATCHDOGTIMERLIB_H

/**@file WatchDogTimerLib.h

  Copyright (c) 2020, Qualcomm Technologies Inc. All rights reserved.<BR>

**/

/*=============================================================================
                              EDIT HISTORY


 when       who     what, where, why
 
 --------   ---     -----------------------------------------------------------
 12/23/20  ds      Initial revision
=============================================================================*/
#include <boot_error_if.h>

/*==============================================================================
**  Functions
**============================================================================*/

/*==============================================================================
  FUNCTION      WatchDog_Enable_Sec

  DESCRIPTION   Set Secure Bit of WatchDog and Enable
  
  Note: Can only be used by NS=0

==============================================================================*/

void WatchDog_Enable_Sec(void);

/*==============================================================================
  FUNCTION      WatchDog_Enable_NSec

  DESCRIPTION   Set Non-Secure Bit of WatchDog and Enable  

==============================================================================*/

void WatchDog_Enable_NSec(void);

/*==============================================================================
  FUNCTION      WatchDog_Disable

  DESCRIPTION   Reset Bit 0 in WDOG_CTL to Disable WatchDogReset 
  
==============================================================================*/

void WatchDog_Disable(void);

/*==============================================================================
  FUNCTION      WatchDog_SetBite_Counter

  DESCRIPTION   Set the WDOG_BITE Counter with value in sleep clocks
  
  Note: If the watchdog Bite timer value is changed while wdog is enabled,
        the new Bite timer value will take effect immediately
==============================================================================*/

bl_error_boot_type WatchDog_SetBite_Counter(uint32 BiteCounterVal);

/*==============================================================================
  FUNCTION      WatchDog_SetBite_MSec

  DESCRIPTION   Set the WDOG_BITE_TIME with the input BiteTime
  
  Note: If the watchdog Bite timer value is changed while wdog is enabled,
        the new Bite timer value will take effect immediately
==============================================================================*/

bl_error_boot_type WatchDog_SetBite_MSec(UINT32 BiteTimeMSec);

/*==============================================================================
  FUNCTION      WatchDog_Pet

  DESCRIPTION   Set the WDOG_RESET register to reset the count in 
                WDOG_STATUS register
==============================================================================*/

void WatchDog_Pet(void);

/*==============================================================================
  FUNCTION      WatchDog_ForceSecBite

  DESCRIPTION   Enable WatchDog and force wdog bite
  
  Note: Can only be used by NS=0
==============================================================================*/

void WatchDog_ForceSecBite(void);

/*==============================================================================
  FUNCTION      WatchDog_ForceSecBite

  DESCRIPTION   Enable WatchDog and force wdog bite
==============================================================================*/

void WatchDog_ForceNSecBite(void);

#endif