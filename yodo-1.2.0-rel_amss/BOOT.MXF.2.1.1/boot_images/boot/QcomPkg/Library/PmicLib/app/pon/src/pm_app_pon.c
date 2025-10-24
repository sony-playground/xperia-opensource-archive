/*! \file pm_app_pon.c
*  
*  \brief Implementation file for PON APP level APIs.
*    
*  &copy; Copyright 2014-2022 QUALCOMM Technologies Incorporated, All Rights Reserved
*/
/*===================================================================
EDIT HISTORY FOR MODULE
 This section contains comments describing changes made to this file.
  Notice that changes are listed in reverse chronological order.

$Date: 2022/08/18 $ 
$Change: 39147961 $
$Header: //components/rel/core.boot/6.1.1/QcomPkg/Library/PmicLib/app/pon/src/pm_app_pon.c#1 $
$Author: pwbldsvc $
$DateTime: 2022/08/18 10:15:46 $
when       who     what, where, why
--------   ---     ---------------------------------------------------------- 
02/16/18   aab     Updated pm_app_pon_pshold_cfg() as per PON App reset recomendation doc
11/19/17   aab     Aded check for RUMI target with out PMIC
08/22/17   czq     Updated pm_app_pon_pshold_cfg() to support DVDD hard reset type.
05/05/16   aab     Updated pm_app_pon_reset_cfg() to support GP1 Configuation 
04/29/16   aab     Added pm_app_pon_reset_init(), used for making any needed pon related init
03/28/16   aab     Updated pm_app_pon_pshold_cfg() to support MSM8998 target
01/22/16   aab     Added pm_log_pon_gen2_reasons()
12/04/15   aab     Updated pm_log_pon_reasons() 
11/11/15   aab     Added back pm_check_pbs_ram_warm_reset_seq_presence() 
10/05/15   aab     Removed Updated pmapp_ps_hold_cfg(). Added pm_app_ps_hold_cfg(), pm_app_pon_reset_cfg() and pm_app_pon_s3_reset_timer_cfg()
09/25/15   aab     Added pm_check_pbs_ram_warm_reset_seq_presence()
08/08/15   aab     Updated pmapp_ps_hold_cfg() to support PON APIs with out doing pmic init
05/31/15   aab     Adding pm_app_log_pon_reasons() and pm_app_log_verbose_pon_reason_status()
04/14/15   al      Adding Hawker support
04/02/15   aab     Updated pmapp_ps_hold_cfg(), 
                    - configure PM8994/PMI8994 individualy instead of using broadcasting command to all 3 PMICs 
01/06/15   kt      Added pmapp_ps_hold_cfg API for multi-pmic config
07/10/14   akm     Creation
===========================================================================*/

/*===========================================================================

                     INCLUDE FILES 

===========================================================================*/
#include "pm_pon.h"
#include "pm_app_pon.h"
#include "pmio_pon.h"
#include "pm_err_flags.h"
#include "device_info.h"
#include "pm_pon_target.h"
#include "pm_sbl_boot.h"
#include "pm_target_information.h"
#include "CoreVerify.h"
#include "pm_device.h"


/*===========================================================================

                     Global Variables

===========================================================================*/
#define PM_MIN_MSEC_PMIC_S3_TIMER (64 * 1000)
#define PON_SPARE_BIT_7 0x80

/*===========================================================================

                   API Implementation

===========================================================================*/
pm_err_flag_type
pm_app_pon_pshold_cfg(pm_app_pon_reset_cfg_type app_pshold_cfg)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  pm_model_type pmic_model  = PMIC_IS_INVALID;
  uint32 pmic_index = 0;
  pm_pon_reset_cfg_type pshold_cfg = PM_PON_RESET_CFG_INVALID;

  if (app_pshold_cfg >= PM_APP_PON_CFG_MAX)
  {
    return PM_ERR_FLAG_INVALID_PARAMETER;
  }

  if ((app_pshold_cfg == PM_APP_PON_CFG_DVDD_HARD_RESET) ||
      (app_pshold_cfg == PM_APP_PON_CFG_DVDD_SHUTDOWN))
  {
    return PM_ERR_FLAG_FEATURE_NOT_SUPPORTED; //SHUTDOWN configs are not supported at this time
  }

  err_flag |= pm_device_setup();
  if (err_flag != PM_ERR_FLAG_SUCCESS)
  {
    return PM_ERR_FLAG_INVALID_PERIPHERAL;
  }

  while (pmic_index < PM_MAX_NUM_PMICS)
  {
    pmic_model = pm_get_pmic_model(pmic_index);

    if ((pmic_model != PMIC_IS_INVALID) && (pmic_model != PMIC_IS_UNKNOWN))
    {
      //Get PMIC specific PSHOLD configuration
      err_flag |= pm_tgt_get_pshold_reset_cfg(pmic_index, app_pshold_cfg, &pshold_cfg);
      if (err_flag != PM_ERR_FLAG_SUCCESS)
      {
        break;
      }

      //PSHOLD Reset Config
      if (pshold_cfg != PON_NO_CFG_NEEDED)
      {
        err_flag |= pm_pon_ps_hold_cfg(pmic_index, pshold_cfg);
      }

      //Target specific reset config
      err_flag |= pm_pon_tgt_specific_pshold_cfg(pmic_index, app_pshold_cfg);
    }
    pmic_index++;
  }

  return err_flag;
}

//Map App level allowed PON reset source enum to PON source enum
static pm_pon_reset_source_type
pm_app_pon_map_app_level_reset_resource(pm_app_pon_reset_source_type app_pon_reset_source)
{
  switch (app_pon_reset_source)
  {
    case PM_APP_PON_RESET_SOURCE_KPDPWR:
      return PM_PON_RESET_SOURCE_KPDPWR;
    case PM_APP_PON_RESET_SOURCE_RESIN:
      return PM_PON_RESET_SOURCE_RESIN;
    case PM_APP_PON_RESET_SOURCE_RESIN_AND_KPDPWR:
      return PM_PON_RESET_SOURCE_RESIN_AND_KPDPWR;
    case PM_APP_PON_RESET_SOURCE_RESIN_OR_KPDPWR:
      return PM_PON_RESET_SOURCE_RESIN_OR_KPDPWR;
    default:
      return PM_PON_RESET_SOURCE_INVALID;
  }
}

pm_err_flag_type
pm_app_pon_reset_cfg(pm_app_pon_reset_source_type app_pon_reset_source,
                     pm_app_pon_reset_cfg_type app_pon_reset_cfg,
                     uint32 s1_timer_ms,
                     uint32 s2_timer_ms)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  pm_model_type pmic_model  = PMIC_IS_INVALID;
  uint32 pmic_index = 0;
  pm_pon_reset_source_type pon_reset_source = PM_PON_RESET_SOURCE_INVALID;
  pm_pon_reset_cfg_type kpdpwr_reset_cfg    = PM_PON_RESET_CFG_INVALID;

  if (app_pon_reset_source >= PM_APP_PON_RESET_SOURCE_MAX)
  {
    return PM_ERR_FLAG_INVALID_PARAMETER;
  }
  else if (app_pon_reset_source == PM_APP_PON_RESET_SOURCE_RESIN_OR_KPDPWR)
  {
    return PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
  }

  if (app_pon_reset_cfg >= PM_APP_PON_CFG_MAX)
  {
    return PM_ERR_FLAG_INVALID_PARAMETER;
  }

  err_flag |= pm_device_setup();
  if (err_flag != PM_ERR_FLAG_SUCCESS)
  {
    return PM_ERR_FLAG_INVALID_PERIPHERAL;
  }

  pon_reset_source = pm_app_pon_map_app_level_reset_resource(app_pon_reset_source);

  if(pon_reset_source == PM_PON_RESET_SOURCE_INVALID)
  {
    return PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
  }

  while (pmic_index < PM_MAX_NUM_PMICS)
  {
    pmic_model = pm_get_pmic_model(pmic_index);

    if ((pmic_model != PMIC_IS_INVALID) && (pmic_model != PMIC_IS_UNKNOWN))
    {
      //Get individual PMIC specific configuration
      err_flag |= pm_tgt_get_kpdpwr_reset_cfg(pmic_index, app_pon_reset_cfg, &kpdpwr_reset_cfg);
      if (err_flag != PM_ERR_FLAG_SUCCESS)
      {
        break;
      }

      //KpadPower/Resin/Key Combo:  Reset Config
      if (kpdpwr_reset_cfg != PON_NO_CFG_NEEDED)
      {
        err_flag |= pm_pon_reset_source_cfg(pmic_index,
                                            pon_reset_source,
                                            s1_timer_ms,
                                            s2_timer_ms,
                                            kpdpwr_reset_cfg);
      }

      //Target specific reset config
      err_flag |= pm_pon_tgt_specific_kpd_reset_cfg(pmic_index, app_pon_reset_cfg);
    }
    pmic_index++;
  }

  return err_flag;
}

pm_err_flag_type 
pm_app_pon_s3_reset_timer_cfg(pm_app_pon_reset_source_type app_pon_s3_reset_source, uint32 s3_timer_ms)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  pm_model_type pmic_model  = PMIC_IS_INVALID;
  uint32 pmic_index = 0;
  pm_pon_reset_source_type pon_s3_reset_source = PM_PON_RESET_SOURCE_INVALID;
  uint32 pm_s3_timer_ms = 0;

  if (app_pon_s3_reset_source >= PM_APP_PON_RESET_SOURCE_MAX)
  {
    return PM_ERR_FLAG_INVALID_PARAMETER;
  }

  err_flag |= pm_device_setup();
  if (err_flag != PM_ERR_FLAG_SUCCESS)
  {
    return PM_ERR_FLAG_INVALID_PERIPHERAL;
  }

  pon_s3_reset_source = pm_app_pon_map_app_level_reset_resource(app_pon_s3_reset_source);

  if(pon_s3_reset_source == PM_PON_RESET_SOURCE_INVALID)
  {
    return PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
  }

  pmic_index = pm_get_primary_pmic_index();

  pmic_model = pm_get_pmic_model(pmic_index);

  if ((pmic_model != PMIC_IS_INVALID) && (pmic_model != PMIC_IS_UNKNOWN))
  {
    pm_s3_timer_ms = s3_timer_ms;
    
    err_flag |= pm_pon_stage3_reset_source_cfg(pmic_index, pon_s3_reset_source, pm_s3_timer_ms);
  }
  else
  {
    return PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
  }

  return err_flag;
}

pm_err_flag_type
pm_pon_uvlo_reset_status(uint32 pmic_device_index, boolean *status)
{
  pm_err_flag_type err_flag   = PM_ERR_FLAG_SUCCESS;
  uint8 pmic_spare_bit        = 0;
  uint8 warm_reset_reason_bit = 0;
  pm_pon_poff_reason_type poff_reason = {0};
  pm_pon_warm_reset_reason_type warm_reset_reason = {0};
  uint8 reg_data;

  pm_pon_get_poff_reason(pmic_device_index, &poff_reason);
  pm_pon_get_warm_reset_reason(pmic_device_index, &warm_reset_reason);
  pm_pon_get_spare_reg(pmic_device_index, PM_PON_XVDD_SPARE, &reg_data);

  /*'pmic_spare_bit' bit<7> of XVDD_RB_SPARE reg is used as a flag for UVLO reset*/

  if (PON_SPARE_BIT_7 == reg_data)
  {
    pmic_spare_bit = 1;
  }

  /* Check if there is any warm reset reason bit is set*/
  warm_reset_reason_bit = warm_reset_reason.gp1 || warm_reset_reason.gp2 ||
                          warm_reset_reason.kpdpwr || warm_reset_reason.kpdpwr_and_resin ||
                          warm_reset_reason.pmic_wd || warm_reset_reason.ps_hold ||
                          //warm_reset_reason.reserved || warm_reset_reason.reserved1 ||
                          warm_reset_reason.resin || warm_reset_reason.soft //||
                          /* warm_reset_reason.tft */;

  /* If poff reason is UVLO and no warm_reset_reason and XVDD_SPARE_REG bit<7> is set, then return 
           UVLO reset status as TRUE */
  if (((poff_reason.gp1 == 1) /* || (poff_reason.uvlo == 1)*/) && (warm_reset_reason_bit == 0) && (pmic_spare_bit == 1))
  {
    *status = TRUE;
  }
  else
  {
    *status = FALSE;
  }

  return err_flag;
}

pm_err_flag_type
pm_app_pon_debug_hard_reset(void)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;

  err_flag = pm_pon_target_debug_hard_reset();

  err_flag |= pm_app_pon_pshold_cfg(PM_APP_PON_CFG_HARD_RESET);

  return err_flag;
}
