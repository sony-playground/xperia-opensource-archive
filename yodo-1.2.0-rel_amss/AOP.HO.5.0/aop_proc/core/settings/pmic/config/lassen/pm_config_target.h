#ifndef __PM_CONFIG_TARGET_H__
#define __PM_CONFIG_TARGET_H__

/*! \file pm_config_target.h
*  \n
*  \brief Contains enums and macro definitions used in config data.
*  \n
*  \n &copy; Copyright 2017 QUALCOMM Technologies Incorporated, All Rights Reserved
*/

/* =======================================================================
                             Edit History
  This section contains comments describing changes made to this file.
  Notice that changes are listed in reverse chronological order.

$Header: //components/rel/aop.ho/5.0/aop_proc/core/settings/pmic/config/lassen/pm_config_target.h#1 $

when       who     what, where, why
--------   ---     ----------------------------------------------------------
07/05/17   kt      Created
========================================================================== */

/*===========================================================================

                     INCLUDE FILES 

===========================================================================*/

#include "drv_mapping.h"

/*===========================================================================

                        TYPE DEFINITIONS

===========================================================================*/

#define PM_DRV_NONE    0x0
#define PM_DRV_TZ     (0x1 << RSC_DRV_GLOBAL_TZ) 
#define PM_DRV_HYP    (0x1 << RSC_DRV_GLOBAL_HYP) 
#define PM_DRV_HLOS   (0x1 << RSC_DRV_GLOBAL_HLOS) 
#define PM_DRV_SEC    (0x1 << RSC_DRV_GLOBAL_SECPROC) 
#define PM_DRV_AUD    (0x1 << RSC_DRV_GLOBAL_AUDIO) 
#define PM_DRV_SEN    (0x1 << RSC_DRV_GLOBAL_SENSORS) 
#define PM_DRV_AOP    (0x1 << RSC_DRV_GLOBAL_AOP) 
#define PM_DRV_DBG    (0x1 << RSC_DRV_GLOBAL_DEBUG) 
#define PM_DRV_GPU    (0x1 << RSC_DRV_GLOBAL_GPU) 
#define PM_DRV_DIS    (0x1 << RSC_DRV_GLOBAL_DISPLAY) 
#define PM_DRV_MDMS   (0x1 << RSC_DRV_GLOBAL_MODEM_SW) 
#define PM_DRV_MDMH   (0x1 << RSC_DRV_GLOBAL_MODEM_HW) 
#define PM_DRV_COM    (0x1 << RSC_DRV_GLOBAL_COMPUTE_DSP) 
#define PM_DRV_ARC    (0x1 << RSC_DRV_GLOBAL_ARC_CPRF)
#define PM_DRV_DDR    (0x1 << RSC_DRV_GLOBAL_DDR_AUX)
#define PM_DRV_WLANBB (0x1 << RSC_DRV_GLOBAL_WLAN_BB)
#define PM_DRV_WLANRF (0x1 << RSC_DRV_GLOBAL_WLAN_RF)



typedef enum
{
  PM_NONE_MODE_VAL     = 0x0,
  PM_BYP_MODE_VAL      = 0x2,
  PM_RET_MODE_VAL      = 0x3,
  PM_LPM_MODE_VAL      = 0x4,
  PM_AUTO_RET_MODE_VAL = 0x5,
  PM_AUTO_MODE_VAL     = 0x6,
  PM_NPM_MODE_VAL      = 0x7,
  PM_INVALID_MODE_VAL  = 0x8,
}pm_mode_val_type; 


#define PM_PRIMARY_SLAVE_ID   0x0

#define PMICLIB_ARCH_PRE7     FALSE


#endif // __PM_CONFIG_TARGET_H__


