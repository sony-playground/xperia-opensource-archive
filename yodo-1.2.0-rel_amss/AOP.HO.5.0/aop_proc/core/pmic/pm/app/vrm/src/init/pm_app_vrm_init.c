/*! \file pm_app_vrm_init.c
 *  \n
 *  \brief Implementation file for VRM resource related application level APIs. 
 *  \n  
 *  \n &copy; Copyright 2016 - 2017 QUALCOMM Technologies Incorporated, All Rights Reserved
 */

/* =======================================================================
                             Edit History
  This section contains comments describing changes made to this file.
  Notice that changes are listed in reverse chronological order.

$Header: //components/rel/aop.ho/5.0/aop_proc/core/pmic/pm/app/vrm/src/init/pm_app_vrm_init.c#1 $
 
when        who     what, where, why
--------    ---     ----------------------------------------------------------
11/23/16    kt       Created
========================================================================== */
/*===========================================================================

                     INCLUDE FILES 

===========================================================================*/
#include "pm_app_vrm_init.h"
#include "pm_debug.h"
#include "pm_rpmh_target.h"
#include "pm_app_pwr.h"
#include "pm_config_target.h"

//******************************************************************************
// Global Data
//******************************************************************************

extern pm_app_vrm_info_type pm_app_vrm_info;

/*===========================================================================

                     API IMPLEMENTATION 

===========================================================================*/
__attribute__((section("rinit_code_sec_pool1")))
pm_err_flag_type pm_app_vrm_init()
{
    pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
         
    pm_debug_info_type *pmic_debug = pm_get_debug_info();
    CORE_VERIFY_PTR(pmic_debug);
    pmic_debug->pm_app_vrm_info = &pm_app_vrm_info;

    if (pm_app_vrm_info.initialized == FALSE)
    {
        // initialize the pmic app vrm lock
        pm_app_vrm_info.lock_count = 0;
        pm_lock_init(&pm_app_vrm_info.lock);

        pm_app_vrm_info.initialized = TRUE;
    }

    return err_flag;
}
