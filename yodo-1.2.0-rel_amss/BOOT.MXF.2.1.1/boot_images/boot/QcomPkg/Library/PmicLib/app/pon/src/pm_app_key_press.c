/*! \file pm_app_key_press.c
*  
*  \brief Implementation file for KEY PRESS APP APIs.
*    
*  &copy; Copyright 2016-2022 QUALCOMM Technologies Incorporated, All Rights Reserved
*/
/*===================================================================
EDIT HISTORY FOR MODULE
 This section contains comments describing changes made to this file.
  Notice that changes are listed in reverse chronological order.

$Date: 2022/08/18 $ 
$Change: 39147961 $
$Header: //components/rel/core.boot/6.1.1/QcomPkg/Library/PmicLib/app/pon/src/pm_app_key_press.c#1 $
$Author: pwbldsvc $
$DateTime: 2022/08/18 10:15:46 $
when       who     what, where, why
--------   ---     ---------------------------------------------------------- 

03/21/16   al     Creation
===========================================================================*/

/*===========================================================================

                     INCLUDE FILES 

===========================================================================*/


#include <Library/BaseLib.h>
#include "TimetickUEFI.h"


#include "pm_pon.h"
#include "pm_prop_ids.h"
#include "pm_target_information.h"
#include "pm_log_utils.h"
#include "pm_app_pon.h"
#include "pm_chg.h"
#include "pm_dt_parser.h"
#include "device_info.h"

#define CONVERSION_MILLISEC_TO_SEC    1000
#define SDAM_PBS_WARMUP_TIME_MILLISEC 100 //100millisec for PBS trigger to get ready
#define KEYPAD_VAL_BYTE               4
#define PON_PBS_BASE_ADDR               0x800
#define PM_HW_MODULE_PON_GEN2_SUBTYPE   4

/*This API checks for conditions that are required for checking invalid power key press check*/
static pm_err_flag_type pm_app_pwrkey_check_press_contions(boolean* chk_condtions);

/*This API monitors the power keypress for specified time*/
static pm_err_flag_type pm_app_pwrkey_monitor_press(pm_pwrkey_dbnc_chk_type  *dbnc_chk, boolean* valid_keypress);

static uint8 pmic_index = 0;
static uint8 kpd_irq_bit = 0;

pm_err_flag_type 
pm_app_pwrkey_long_press_check(pm_pon_pwrkey_dbnc_chk_at_type  dbnc_chk_at)
{
  pm_err_flag_type         err_flag = PM_ERR_FLAG_SUCCESS;
  boolean                  chk_condtions = FALSE;
#ifndef FEATURE_XBOOT
  boolean                  valid_keypress = FALSE;
#endif /* !FEATURE_XBOOT */
  pm_pwrkey_dbnc_chk_type  *dbnc_chk = NULL;
  pm_dt_pon_config         *pon_config = NULL;
  peripheral_info_type     periph_info = {0};
  
  dbnc_chk = (pm_pwrkey_dbnc_chk_type *)pm_target_information_get_specific_info(PM_PROP_LONG_PWRKEY_HOLD_BOOT_TIME);
  if(NULL == dbnc_chk)
  {
    return PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
  }
  
  pon_config = pm_dt_get_node( PMIC_DT_NODE_PM_PON );
  if(pon_config != NULL)
  {
	 dbnc_chk->chk_at = pon_config->dbnc_chk_at;
     dbnc_chk->dbnc_time_msec = pon_config->dbnc_time_ms;	 
  }

  /*return if check is not to be done from current image or wait time is 0 millisecond*/
  if((dbnc_chk->chk_at != dbnc_chk_at) || (dbnc_chk->dbnc_time_msec == 0))
  {
    return PM_ERR_FLAG_SUCCESS;
  }

  pmic_index = dbnc_chk->pmic_index;
  
  periph_info.base_address = PON_PBS_BASE_ADDR;
  err_flag |= pm_get_peripheral_info (pmic_index, &periph_info);
  kpd_irq_bit = (periph_info.peripheral_subtype == PM_HW_MODULE_PON_GEN2_SUBTYPE) ? PM_PON_IRQ_KPDPWR_N_S2 : PM_PON_IRQ_KPD_PWR_N_DEB;
 
  /*verify if all conditions to check for invalid power keypress are satisfied */
  err_flag = pm_app_pwrkey_check_press_contions(&chk_condtions);
  if(((FALSE == chk_condtions) && (PM_ERR_FLAG_SUCCESS == err_flag)) 
     || (PM_ERR_FLAG_SUCCESS != err_flag ))
  {
      return err_flag;
  }

#ifndef FEATURE_XBOOT
 /*monitor key press for dbnc_time_msec time*/
  err_flag |= pm_app_pwrkey_monitor_press(dbnc_chk, &valid_keypress);
  if((FALSE == valid_keypress) && (PM_ERR_FLAG_SUCCESS == err_flag))
  {
    pm_log_message("Invalid pwrkey press. Shutting down! \n\r");

	
    pm_device_shutdown();
  }
#endif /* !FEATURE_XBOOT */

  return err_flag;
}



static pm_err_flag_type 
pm_app_pwrkey_check_press_contions(boolean* chk_condtions)
{
  pm_err_flag_type            err_flag = PM_ERR_FLAG_SUCCESS;
  pm_pon_on_state_reason_type on_reason = {0};
  pm_pon_reason_type          pon_reason = {0};
  boolean charger_present = FALSE;

  if(NULL == chk_condtions)
  {
    return PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
  }
  /*initialize */
  *chk_condtions = FALSE;

  /*read the on reason and if warm reset then return*/
  err_flag = pm_pon_get_on_reason(pmic_index, &on_reason);
  if(PMIC_IS_PM855 == pm_get_pmic_model(pmic_index))
  {
    //Wailua PON register bit map is different , checking the 7th bit (pon_seq) of on_reason 
    if((on_reason.hard_reset_seq != TRUE) || (err_flag != PM_ERR_FLAG_SUCCESS))
    {
      return err_flag;
    }
  }
  else 
  {
    if((on_reason.pon_seq != TRUE) || (err_flag != PM_ERR_FLAG_SUCCESS))
    {
      return err_flag;
    }
  }

  err_flag |= pm_pon_get_pon_reason(pmic_index, &pon_reason);
  if(PM_ERR_FLAG_SUCCESS != err_flag)
  {
    return err_flag;
  }
  
  err_flag = pm_chg_is_vbus_present(&charger_present);
  
  if(err_flag != PM_ERR_FLAG_SUCCESS)
  {
	charger_present = FALSE;  
	/*set it to SUCCESS since VBUS API will return failure
     if charger pmic not present*/
	err_flag = PM_ERR_FLAG_SUCCESS;
  }
  
  
  
  /*if PON reason is key press alone then set the condition TRUE*/
  if((pon_reason.kpdpwr) && ( !( pon_reason.smpl | pon_reason.rtc | pon_reason.dc_chg | 
                               pon_reason.usb_chg | pon_reason.pon1 | pon_reason.cblpwr | 
                               pon_reason.hard_reset)) 
						 && (!charger_present)
     )
  {
    *chk_condtions = TRUE;
  }

  return err_flag;
}


/*This API checks if key was pressed for desired duration before it was released by reading press and release time from SDAM registers. 
  If key is still pressed then the API will simply return VALID keypress, since this API is called during boot if valid keypress time had already elapsed   */
static boolean pm_app_pwrkey_was_keypress_release_valid(pm_pwrkey_dbnc_chk_type  *dbnc_chk)
{
   pm_err_flag_type      err_flag = PM_ERR_FLAG_SUCCESS;
   boolean               key_press_rt_sts = TRUE;
   uint32                press_time = 0;
   uint32                release_time = 0;
   int32                 debounce_time = 0;
   boolean               valid_keypress = TRUE;
   uint8                 pmic_rev = pm_get_pmic_revision(pmic_index);

   if ((NULL != dbnc_chk)
       && (TRUE == dbnc_chk->sdam_dbnc_supported)
       && (pmic_rev >= dbnc_chk->min_pmic_rev))
   {
      err_flag |= pm_pon_irq_status(pmic_index, (pm_pon_irq_type)kpd_irq_bit, PM_IRQ_STATUS_RT, &key_press_rt_sts);
      if (key_press_rt_sts == FALSE)
      {
         //check for SDAM time
         err_flag |= pm_sdam_mem_read(pmic_index, dbnc_chk->sdam_periph_index, dbnc_chk->sdam_key_press_offset, KEYPAD_VAL_BYTE, (pm_register_data_type*)&press_time);
         err_flag |= pm_sdam_mem_read(pmic_index, dbnc_chk->sdam_periph_index, dbnc_chk->sdam_key_release_offset, KEYPAD_VAL_BYTE, (pm_register_data_type*)&release_time);

         debounce_time = release_time - press_time;      
        
         if ((dbnc_chk->dbnc_time_msec > debounce_time) && (err_flag == PM_ERR_FLAG_SUCCESS))
         {
            pm_log_message("Boot up PwrKey press %d ms detected is less than expected %d ms duration. Shutting down device. Release_time %d, Press_time %d \n\r", 
                            debounce_time, dbnc_chk->dbnc_time_msec, release_time, press_time);
            valid_keypress = FALSE;
         }
     
      }
   }

   return valid_keypress;
}


pm_err_flag_type 
pm_app_pwrkey_monitor_press(pm_pwrkey_dbnc_chk_type  *dbnc_chk, boolean* valid_keypress)
{
  pm_err_flag_type   err_flag = PM_ERR_FLAG_SUCCESS;
  uint64             elapsed_tick = 0;
  uint32             timetick_freq = 0;
  uint64             wait_tick = 0;
  boolean            key_press_rt_sts = TRUE;
  uint64             sdam_pbs_ready_tick = 0;
  
  if((NULL == dbnc_chk) || (NULL == valid_keypress) || (dbnc_chk->dbnc_time_msec == 0))
  {
    return PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
  }

  /*initialize with TRUE*/ 
  *valid_keypress = TRUE;

  /*Initialize Timetick, get current frequency*/
  Timetick_Init();
  Timetick_GetFreq(TIMETICK_QTIMER, &timetick_freq);

   /*convert wait time to tick at current fequency*/
  wait_tick = MultU64x32(dbnc_chk->dbnc_time_msec, timetick_freq);

  sdam_pbs_ready_tick = MultU64x32(SDAM_PBS_WARMUP_TIME_MILLISEC, timetick_freq);

  if(wait_tick && sdam_pbs_ready_tick)
  {
    wait_tick = DivU64x32(wait_tick, CONVERSION_MILLISEC_TO_SEC);
    sdam_pbs_ready_tick = DivU64x32(sdam_pbs_ready_tick, CONVERSION_MILLISEC_TO_SEC);
  }
  else
  {
    return err_flag;
  }

  /*Get ticks elapsed since device powered on and compare*/
  (void)Timetick_GetCount(TIMETICK_QTIMER, &elapsed_tick);
 
  /* if time amounting to keypress has already elapsed then read SDAM to get debounce time */
  if ((elapsed_tick >= wait_tick) && (elapsed_tick >= sdam_pbs_ready_tick))
  {
    *valid_keypress = pm_app_pwrkey_was_keypress_release_valid(dbnc_chk);
  }
  else
  {
     while(elapsed_tick < wait_tick)
     {
       /*wait 50usec in between reads*/
       pm_busy_wait(50);

       /*check for if key still pressed. If FALSE then read again to confirm*/
       err_flag |= pm_pon_irq_status(pmic_index, (pm_pon_irq_type)kpd_irq_bit, PM_IRQ_STATUS_RT, &key_press_rt_sts);
       
       if(key_press_rt_sts == FALSE)
       {
         err_flag |= pm_pon_irq_status(pmic_index, (pm_pon_irq_type)kpd_irq_bit, PM_IRQ_STATUS_RT, &key_press_rt_sts);
         if(key_press_rt_sts == FALSE)
         {
           pm_log_message("Elapsed tick: 0x%x, Wait tick: 0x%x \n\r", elapsed_tick, wait_tick);
           *valid_keypress = FALSE;
           break;
         }
       }

       Timetick_GetCount(TIMETICK_QTIMER, &elapsed_tick);
     }
  }

  return err_flag;
}



