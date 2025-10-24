/*! \file
*
*  \brief  pm_app_pon.c
*  \details Implementation file for rgb led resourece type.
*
*  &copy; Copyright 2014-2021 QUALCOMM Technologies Incorporated, All Rights Reserved
*/

/*===========================================================================

EDIT HISTORY FOR MODULE

This document is created by a code generator, therefore this section will
not contain comments describing changes made to the module.

$Header: //components/rel/aop.ho/5.0/aop_proc/core/pmic/pm/app/pon/src/pm_app_pon_key_reset.c#1 $
$Date: 2021/10/26 $
$Change: 33677139 $
when       who     what, where, why
--------   ---     ----------------------------------------------------------
04/03/18   akm     Updated pm_err_flags
02/02/17   akm     Moved PMIC,SPMI out to Systemdrivers
04/15/15   aab     Updated pm_app_ps_hold_cfg
02/03/15   rk      Added pmapp_ps_hold_cfg API for multi-pmic config
07/10/14   akm     Creation
===========================================================================*/

/*===========================================================================

                     INCLUDE FILES

===========================================================================*/
#include "pm_pon.h"
#include "pm_err_flags.h"
#include "device_info.h"
#include "pm_comm.h"
#include "pm_pon_cfg.h"
#include "pm_target_information.h"
#include "pm_config_target.h"


#define PM_MIN_MSEC_PMIC_S3_TIMER (64 * 1000)

/*===========================================================================

                     Function Implementation

===========================================================================*/
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

  err_flag = pm_comm_channel_init_internal();
  
  if (err_flag != PM_ERR_FLAG_SUCCESS)
  {
    return PM_ERR_FLAG_INVALID_PERIPHERAL;
  }

  //Map App level allowed PON reset source enum to PON source enum
  switch (app_pon_reset_source)
  {
  case PM_APP_PON_RESET_SOURCE_KPDPWR:
  {
    pon_reset_source = PM_PON_RESET_SOURCE_KPDPWR;
  }
  break;
  case PM_APP_PON_RESET_SOURCE_RESIN:
  {
    pon_reset_source = PM_PON_RESET_SOURCE_RESIN;
  }
  break;
  case PM_APP_PON_RESET_SOURCE_RESIN_AND_KPDPWR:
  {
    pon_reset_source = PM_PON_RESET_SOURCE_RESIN_AND_KPDPWR;
  }
  break;
  default:
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
  boolean skip_reset_config = FALSE;
  pm_model_type pmic_model  = PMIC_IS_INVALID;
  uint32 pmic_index = 0;
  pm_pon_reset_source_type pon_s3_reset_source = PM_PON_RESET_SOURCE_INVALID;
  uint32 pm_s3_reset_timer_multiplier;
  uint32 pm_s3_timer_ms;

  if (app_pon_s3_reset_source >= PM_APP_PON_RESET_SOURCE_MAX)
  {
    return PM_ERR_FLAG_INVALID_PARAMETER;
  }

  /* Init SPMI driver context. */
  err_flag = pm_comm_channel_init_internal();
  
  if (err_flag != PM_ERR_FLAG_SUCCESS)
  {
    return PM_ERR_FLAG_INVALID_PERIPHERAL;
  }

  //Map App level allowed PON reset source enum
  switch (app_pon_s3_reset_source)
  {
  case PM_APP_PON_RESET_SOURCE_KPDPWR:
  {
    pon_s3_reset_source = PM_PON_RESET_SOURCE_KPDPWR;
  }
  break;
  case PM_APP_PON_RESET_SOURCE_RESIN:
  {
    pon_s3_reset_source = PM_PON_RESET_SOURCE_RESIN;
  }
  break;
  case PM_APP_PON_RESET_SOURCE_RESIN_AND_KPDPWR:
  {
    pon_s3_reset_source = PM_PON_RESET_SOURCE_RESIN_AND_KPDPWR;
  }
  break;
  case PM_APP_PON_RESET_SOURCE_RESIN_OR_KPDPWR:
  {
    pon_s3_reset_source = PM_PON_RESET_SOURCE_RESIN_OR_KPDPWR;
  }
  break;
  default:
    return PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
  }

  while (pmic_index < PM_MAX_NUM_PMICS)
  {
    pmic_model = pm_get_pmic_model(pmic_index);
    skip_reset_config = FALSE;

    if ((pmic_model != PMIC_IS_INVALID) && (pmic_model != PMIC_IS_UNKNOWN))
    {
      //Get individual PMIC specific configuration
      err_flag |= pm_tgt_get_pon_s3_reset_timer_multiplier(pmic_index, app_pon_s3_reset_source, &pm_s3_reset_timer_multiplier);
      if (err_flag != PM_ERR_FLAG_SUCCESS)
      {
        break;
      }

      if (pm_s3_reset_timer_multiplier != 0)
      { //Configure S3 reset timer
        pm_s3_timer_ms = s3_timer_ms * pm_s3_reset_timer_multiplier;

        //S3 timer value for all Secondary PMICs should be at least 64 sec
        if ((pmic_index > 0) && (pm_s3_timer_ms < PM_MIN_MSEC_PMIC_S3_TIMER))
        {
          pm_s3_timer_ms = PM_MIN_MSEC_PMIC_S3_TIMER;
        }
        err_flag |= pm_pon_stage3_reset_source_cfg(pmic_index, pon_s3_reset_source, pm_s3_timer_ms);
      }
    }
    pmic_index++;
  }

  return err_flag;
}
