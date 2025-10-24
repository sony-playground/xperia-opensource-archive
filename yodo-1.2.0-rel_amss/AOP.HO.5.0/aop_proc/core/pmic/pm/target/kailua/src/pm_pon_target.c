/*! \file
*  \n
*  \brief  pm_pon_target.c
*  \n
*  \n This file contains pmic configuration data specific for PON sequence
*     for SDM845 device.
*  \n
*  \n &copy; Copyright 2017-2021 QUALCOMM Technologies Incorporated, All Rights Reserved
*/
/* =======================================================================
Edit History
This section contains comments describing changes made to this file.
Notice that changes are listed in reverse chronological order.

$Header: //components/rel/aop.ho/5.0/aop_proc/core/pmic/pm/target/kailua/src/pm_pon_target.c#1 $

when       who     what, where, why
--------   ---     ----------------------------------------------------------
04/03/18   akm     Updated pm_err_flags
06/26/17   akm     Created
========================================================================== */

/*=========================================================================
      Include Files
==========================================================================*/

#include "pm_pon_cfg.h"
#include "device_info.h"



/*===========================================================================
Data Declarations
===========================================================================*/
//PSHOlD config:  PON PS Hold config
static const uint8
pm_pon_pshold_reset_cfg_arr[PM_APP_PON_CFG_MAX][PM_MAX_NUM_PMICS] =
{  //Tokei
   {PON_WARM_RST,      PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED, PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED, PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED}, //Warm Reset
   {PON_HARD_RST,      PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED, PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED, PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED}, //Hard Reset
   {PON_SHDN,          PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED, PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED, PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED}, //Shutdown
   {PON_NO_CFG_NEEDED, PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED, PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED, PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED}, //Dvdd hard reset
   {PON_NO_CFG_NEEDED, PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED, PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED, PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED}  //DVDD Shutdown
};


//PSHOlD config:  PON GP1 config
static const uint8
pm_pon_pshold_gp1_reset_cfg_arr[PM_APP_PON_CFG_MAX][PM_MAX_NUM_PMICS] =
{  //Tokei
   {PON_NO_CFG_NEEDED, PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED, PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED, PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED}, //Warm Reset
   {PON_NO_CFG_NEEDED, PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED, PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED, PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED}, //Hard Reset
   {PON_NO_CFG_NEEDED, PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED, PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED, PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED}, //Shutdown
   {PON_NO_CFG_NEEDED, PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED, PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED, PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED}, //Dvdd hard reset
   {PON_NO_CFG_NEEDED, PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED, PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED, PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED}  //DVDD Shutdown
};

//Kpdpwr / Resin /Key Combo(Resin_and_Kpdpwr):  PON Keypad Power S2 Config
static const pm_pon_reset_cfg_type
pm_app_pon_kpdpwr_reset_cfg_arr[PM_APP_PON_CFG_MAX][PM_MAX_NUM_PMICS] =
{  //Tokei
   {PON_WARM_RST,      PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED, PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED }, //Warm Reset
   {PON_HARD_RST,      PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED, PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED }, //Hard Reset
   {PON_SHDN,          PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED, PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED }, //Shutdown
   {PON_NO_CFG_NEEDED, PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED, PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED }, //Dvdd hard reset
   {PON_NO_CFG_NEEDED, PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED, PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED,  PON_NO_CFG_NEEDED }  //DVDD Shutdown
};

//S3 reset Timer Config
static const uint8
pm_app_pon_s3_reset_timer_multiplier_arr[PM_APP_PON_RESET_SOURCE_MAX][PM_MAX_NUM_PMICS] =
{  
   { 0,         0,      0,          0,       0,           0, 0},    //KPDPWR_N
   { 0,         0,      0,          0,       0,           0, 0},    //RESIN_N
   { 0,         0,      0,          0,       0,           0, 0},    //KPDPWR_AND_RESIN
   { 0,         0,      0,          0,       0,           0, 0}     //KPDPWR_OR_RESIN
};

/*=========================================================================
      Function Prototypes
==========================================================================*/
pm_err_flag_type 
pm_tgt_get_pshold_gp1_reset_cfg( uint32                      pmic_index,
                                 pm_app_pon_reset_cfg_type   app_pshold_gp1_cfg,
                                 pm_pon_reset_cfg_type*      pshold_gp1_cfg);




/* ============================================================================
**    Functions
** ==========================================================================*/

pm_err_flag_type
pm_tgt_get_pshold_reset_cfg( uint32                      pmic_index,
                             pm_app_pon_reset_cfg_type   app_pshold_cfg,
                             pm_pon_reset_cfg_type*      pshold_cfg)
{
  if( (pmic_index         >=  PM_MAX_NUM_PMICS)   ||  
      (app_pshold_cfg     >=  PM_APP_PON_CFG_MAX) ||
      (pshold_cfg         ==  NULL) )
{
    return PM_ERR_FLAG_INVALID_PARAMETER;
  }

  *pshold_cfg = pm_pon_pshold_reset_cfg_arr[app_pshold_cfg][pmic_index];

  return PM_ERR_FLAG_SUCCESS;
}



pm_err_flag_type 
pm_tgt_get_pshold_gp1_reset_cfg( uint32                      pmic_index,
                                 pm_app_pon_reset_cfg_type   app_pshold_gp1_cfg,
                                 pm_pon_reset_cfg_type*      pshold_gp1_cfg)
{
  if( (pmic_index           >=  PM_MAX_NUM_PMICS)   ||  
      (app_pshold_gp1_cfg   >=  PM_APP_PON_CFG_MAX) ||
      (pshold_gp1_cfg       ==  NULL) )
  {
    return PM_ERR_FLAG_INVALID_PARAMETER;
}

  *pshold_gp1_cfg = pm_pon_pshold_gp1_reset_cfg_arr[app_pshold_gp1_cfg][pmic_index];

  return PM_ERR_FLAG_SUCCESS;
}



pm_err_flag_type
pm_pon_tgt_specific_pshold_cfg(uint32 pmic_index, pm_app_pon_reset_cfg_type app_pshold_cfg)
{
   pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
   pm_pon_reset_cfg_type       pshold_gp1_cfg  = PM_PON_RESET_CFG_INVALID;

   if( (pmic_index >=  PM_MAX_NUM_PMICS ) || (app_pshold_cfg >=  PM_APP_PON_CFG_MAX))
   {
     return PM_ERR_FLAG_INVALID_PARAMETER;
   }

   //GP1 Reset Config
   err_flag |= pm_tgt_get_pshold_gp1_reset_cfg(pmic_index, app_pshold_cfg,  &pshold_gp1_cfg); 
   if (pshold_gp1_cfg != PON_NO_CFG_NEEDED) 
   { 
       err_flag |= pm_pon_gp_reset_cfg( pmic_index, PM_PON_RESET_SOURCE_GP1, pshold_gp1_cfg);
   }
   
   return err_flag;
}

pm_err_flag_type
pm_tgt_get_kpdpwr_reset_cfg( uint32                        pmic_index,
                             pm_app_pon_reset_cfg_type     app_kpdpwr_reset_cfg,
                             pm_pon_reset_cfg_type*        kpdpwr_reset_cfg)
{
    pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;

    if( (pmic_index             >= PM_MAX_NUM_PMICS)   ||
        (app_kpdpwr_reset_cfg   >= PM_APP_PON_CFG_MAX) ||
        (kpdpwr_reset_cfg       == NULL) )
    {
       return PM_ERR_FLAG_INVALID_PARAMETER;
    }

    *kpdpwr_reset_cfg = pm_app_pon_kpdpwr_reset_cfg_arr[app_kpdpwr_reset_cfg][pmic_index];

    return err_flag;
}

pm_err_flag_type
pm_tgt_get_pon_s3_reset_timer_multiplier( uint32                        pmic_index,
                                          pm_app_pon_reset_source_type  app_pon_s3_reset_source,
                                          uint32*                       pm_s3_reset_timer_multiplier )
{
    pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;

    if( (pmic_index                   >= PM_MAX_NUM_PMICS)           ||
        (app_pon_s3_reset_source      >= PM_APP_PON_RESET_SOURCE_MAX)||
        (pm_s3_reset_timer_multiplier == NULL) )
    {
       return PM_ERR_FLAG_INVALID_PARAMETER;
    }

    *pm_s3_reset_timer_multiplier = pm_app_pon_s3_reset_timer_multiplier_arr[app_pon_s3_reset_source][pmic_index];

    return err_flag;
}

pm_err_flag_type
pm_pon_tgt_specific_kpd_reset_cfg(uint32 pmic_index, pm_app_pon_reset_cfg_type app_pon_reset_cfg)
{
   pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
   //Add target specific config
   return err_flag;
}


