/*! \file
*
*  \brief  pm_app_pon.c
*  \details Implementation file for rgb led resourece type.
*
*  &copy; Copyright 2014-2018 QUALCOMM Technologies Incorporated, All Rights Reserved
*/

/*===========================================================================

EDIT HISTORY FOR MODULE

This document is created by a code generator, therefore this section will
not contain comments describing changes made to the module.

$Header: //components/rel/aop.ho/5.0/aop_proc/core/pmic/pm/app/pon/src/pm_app_pon.c#1 $
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



/*===========================================================================

                     Function Implementation

===========================================================================*/
/**
 * @brief This function performs Warm Reset or Shutdown for all PMICs.
 *
 * @details The function detects all PMICs and configures PSHOLD to shutdown PMIC
 *          devices.
 *
 * @param[in] pon_cfg - support configurations:
 *                       PM_APP_PON_CFG_WARM_RESET,
 *                       PM_APP_PON_CFG_HARD_RESET,
 *                       PM_APP_PON_CFG_NORMAL_SHUTDOWN,
 *
 * @return pm_err_flag_type PM_ERR_FLAG_SUCCESS on success otherwise PMIC error.
 *
 *
 */
 pm_err_flag_type pm_app_ps_hold_cfg(pm_app_pon_reset_cfg_type app_pshold_cfg)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  pm_model_type pmic_model = PMIC_IS_INVALID;
  uint32 pmic_index = 0;
  pm_pon_reset_cfg_type       pshold_cfg         = PM_PON_RESET_CFG_INVALID;


  if (app_pshold_cfg >= PM_APP_PON_CFG_MAX) 
  {
      return PM_ERR_FLAG_INVALID_PARAMETER;
  }

  if ((app_pshold_cfg == PM_APP_PON_CFG_DVDD_HARD_RESET) || 
      (app_pshold_cfg == PM_APP_PON_CFG_DVDD_SHUTDOWN)) 
  {
     return PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;//HARD_RESET / SHUTDOWN configs are not supported at this time
  }


  /* Init SPMI driver context. */
  err_flag = pm_comm_channel_init_internal();
  if (err_flag != PM_ERR_FLAG_SUCCESS)
  {
    return err_flag;
  }
  /* Find PMIC devices. */
  err_flag = pm_version_detect();
  if (err_flag != PM_ERR_FLAG_SUCCESS)
  {
    return err_flag;
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
  }//while

  return err_flag;

} /* pm_app_ps_hold_cfg */

