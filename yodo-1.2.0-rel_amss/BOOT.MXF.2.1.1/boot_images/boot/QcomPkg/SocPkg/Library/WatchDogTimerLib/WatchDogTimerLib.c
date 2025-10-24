/**@file WatchDogTimerLib.c

  Copyright (c) 2020, Qualcomm Technologies Inc. All rights reserved.<BR>

**/

/*=============================================================================
                              EDIT HISTORY


 when       who     what, where, why
 
 --------   ---     -----------------------------------------------------------
 12/23/20  ds      Initial revision
=============================================================================*/
#include <Library/ArmLib.h>
#include <WatchDogTimerLib.h>
#include <HALbootHWIO.h>
#include <HALhwio.h>

#define SLEEP_CLK_FREQ             32768

#define MAX_WDOG_COUNTER_VAL       (1 << 20)

#define MS_TO_WDOG_COUNTER_VAL(x)  ((((x) * SLEEP_CLK_FREQ) / 1000) - 1)

#define MAX_WDOG_BITE_VAL          (MAX_WDOG_COUNTER_VAL - 1)

#define FORCED_BITE_TIME_MS        4

/*==============================================================================
**  Functions
**============================================================================*/

/*==============================================================================
  FUNCTION      WatchDog_Enable

  DESCRIPTION   Set Bit 0 in WDOG_CTL to Enable WatchDog 
  

==============================================================================*/

static void WatchDog_Enable(void)
{
  HWIO_APSS_WDT_TMR1_WDOG_CTL_OUT(HWIO_APSS_WDT_TMR1_WDOG_CTL_INT_ENABLE_ENABLE_FVAL);
  ArmInstructionSynchronizationBarrier();
}

/*==============================================================================
  FUNCTION      WatchDog_Enable_Sec

  DESCRIPTION   Set Secure Bit of WatchDog and Enable
  
  Note: Can only be used by NS=0

==============================================================================*/

void WatchDog_Enable_Sec(void)
{
  HWIO_APSS_WDT_TMR1_WDOG_SECURE_OUT(HWIO_APSS_WDT_TMR1_WDOG_SECURE_WDT_SEC_FVAL);
  ArmInstructionSynchronizationBarrier();
  
  WatchDog_Enable();
}

/*==============================================================================
  FUNCTION      WatchDog_Enable_NSec

  DESCRIPTION   Set Non-Secure Bit of WatchDog and Enable  

==============================================================================*/

void WatchDog_Enable_NSec(void)
{
  HWIO_APSS_WDT_TMR1_WDOG_SECURE_OUT(HWIO_APSS_WDT_TMR1_WDOG_SECURE_WDT_NSEC_FVAL);
  ArmInstructionSynchronizationBarrier();
  
  WatchDog_Enable();
}
/*==============================================================================
  FUNCTION      WatchDog_Disable

  DESCRIPTION   Reset Bit 0 in WDOG_CTL to Disable WatchDogReset 
  
==============================================================================*/

void WatchDog_Disable(void)
{
  HWIO_APSS_WDT_TMR1_WDOG_CTL_OUT(HWIO_APSS_WDT_TMR1_WDOG_CTL_INT_ENABLE_DISABLE_FVAL);
  ArmInstructionSynchronizationBarrier ();
}

/*==============================================================================
  FUNCTION      WatchDog_SetBite_Counter

  DESCRIPTION   Set the WDOG_BITE Counter with value in sleep clocks
  
  Note: If the watchdog Bite timer value is changed while wdog is enabled,
        the new Bite timer value will take effect immediately
==============================================================================*/


bl_error_boot_type WatchDog_SetBite_Counter(uint32 BiteCounterVal)
{
  if ((BiteCounterVal == 0) || (BiteCounterVal > MAX_WDOG_BITE_VAL))
    return GET_ERROR_CODE(BL_ERROR_GROUP_WDOGTMR, BL_ERR_INVALID_PARAMETER);;
  
  HWIO_APSS_WDT_TMR1_WDOG_BITE_TIME_OUT(BiteCounterVal);

  ArmInstructionSynchronizationBarrier();
  
  WatchDog_Pet();
  
  return BL_ERR_NONE;  
}


/*==============================================================================
  FUNCTION      WatchDog_SetBite_MSec

  DESCRIPTION   Set the WDOG_BITE_TIME with the input BiteTime
  
  Note: If the watchdog Bite timer value is changed while wdog is enabled,
        the new Bite timer value will take effect immediately
==============================================================================*/

bl_error_boot_type WatchDog_SetBite_MSec(UINT32 BiteTimeMSec)
{
  UINT32 BiteTimeCounterVal = MS_TO_WDOG_COUNTER_VAL(BiteTimeMSec);

  return WatchDog_SetBite_Counter(BiteTimeCounterVal);
}

/*==============================================================================
  FUNCTION      WatchDog_Pet

  DESCRIPTION   Set the WDOG_RESET register to reset the count in 
                WDOG_STATUS register
==============================================================================*/

void WatchDog_Pet(void)
{
  //Reset Wdog count to start from 0 again
  
  HWIO_APSS_WDT_TMR1_WDOG_RESET_OUT(HWIO_APSS_WDT_TMR1_WDOG_RESET_RESET_BMSK);
  ArmInstructionSynchronizationBarrier();
}

/*==============================================================================
  FUNCTION      WatchDog_ForceSecBite

  DESCRIPTION   Enable WatchDog and force wdog bite
  
  Note: Can only be used by NS=0
==============================================================================*/

void WatchDog_ForceSecBite(void)
{
  /* CTL, Enable */
  WatchDog_Enable_Sec();
  
  WatchDog_Pet();

  WatchDog_SetBite_MSec(FORCED_BITE_TIME_MS);
  ArmInstructionSynchronizationBarrier();
  
  while(1);
}

/*==============================================================================
  FUNCTION      WatchDog_ForceSecBite

  DESCRIPTION   Enable WatchDog and force wdog bite
==============================================================================*/

void WatchDog_ForceNSecBite(void)
{
  /* CTL, Enable */
  WatchDog_Enable_NSec();
  
  WatchDog_Pet();

  WatchDog_SetBite_MSec(FORCED_BITE_TIME_MS);
  ArmInstructionSynchronizationBarrier();
  
  while(1);
}