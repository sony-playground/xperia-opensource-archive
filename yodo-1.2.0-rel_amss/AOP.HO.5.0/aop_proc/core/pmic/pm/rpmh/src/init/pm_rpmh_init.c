/*! \file
*  
*  \brief  pm_rpmh_init.c ----This file contains driver functions for rpmh 
*                        communication 
*
* Copyright (c) 2017 QUALCOMM Technologies, Inc. (QTI). All Rights Reserved.  
* QUALCOMM Proprietary.  Export of this technology or software is regulated 
* by the U.S. Government. Diversion contrary to U.S. law prohibited.  
*/
/*===========================================================================

                        EDIT HISTORY FOR MODULE

  This section contains comments describing changes made to the module.
  Notice that changes are listed in reverse chronological order.

$Header: //components/rel/aop.ho/5.0/aop_proc/core/pmic/pm/rpmh/src/init/pm_rpmh_init.c#1 $
  
when       who     what, where, why
--------   ---     ---------------------------------------------------------- 
01/10/17   akm     Created
===========================================================================*/
/*===========================================================================

                     INCLUDE FILES FOR MODULE

===========================================================================*/
#include "pm_rpmh.h"

/*===========================================================================

                     GLOBAL VARIABLES FOR MODULE 

===========================================================================*/

extern rpmh_client_handle pm_rpmh_h; 

/*===========================================================================

                     FUNCTION DEFINITIONS 

===========================================================================*/
__attribute__((section("rinit_code_sec_pool1")))
void 
pm_rpmh_init(void)
{
    uint32* rpmh_drv_id = NULL;
    
    //rpmh_client_init ();

    rpmh_drv_id = pm_target_information_get_specific_info(PM_PROP_RPMH_DRV_ID);
    CORE_VERIFY_PTR(rpmh_drv_id);
 
    pm_rpmh_h = rpmh_create_handle((RSCSW_DRV_MAPPING)*rpmh_drv_id, "pmic");
    
    if(pm_rpmh_h == NULL)
        CORE_VERIFY(0);
        //PM_LOG_MSG_ERR_FATAL("Unable to obtain rpmh handle");
        
    return;
}
