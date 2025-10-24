/*! \file pm_vrm.c
 *  \n
 *  \brief This file contains implementation for PMIC VRM initialization.
 *  \n  
 *  \n &copy; Copyright 2016 - 2017 QUALCOMM Technologies Incorporated, All Rights Reserved
 */

/* =======================================================================
                             Edit History
  This section contains comments describing changes made to this file.
  Notice that changes are listed in reverse chronological order.

$Header: //components/rel/aop.ho/5.0/aop_proc/core/pmic/pm/vrm/src/pm_vrm.c#1 $  

when       who     what, where, why
--------   ---     ---------------------------------------------------------- 
08/29/16   kt     Created
===========================================================================*/
/*===========================================================================

                        INCLUDE FILES

===========================================================================*/

#include "pm_vrm.h"
#include "pm_app_vrm_init.h"
#include "device_info.h"
#include "page_select.h"


/*===========================================================================

                  LOCAL CONSTANT AND MACRO DEFINITIONS

===========================================================================*/

/*===========================================================================

                         LOCAL FUNCTION PROTOTYPES

===========================================================================*/

/*===========================================================================

                           VARIABLES DEFINITIONS

===========================================================================*/


/*===========================================================================

                            FUNCTION DEFINITIONS

===========================================================================*/

pm_err_flag_type pm_vrm_get_drv_mask(uint32 drv_mask, uint32* ret_drv_mask)
{
   uint32 drv_id = 0;
   uint32 new_drv_id = 0;
   *ret_drv_mask = 0;

   for(drv_id = 0; drv_id < VRM_RSC_DRV_MAX; drv_id++)
   {
      if(((drv_mask >> drv_id) & 0x1)
         && (get_version_drv_id(drv_id, &new_drv_id) == DRV_ID_LOOKUP_SUCCESS)
         )
      {
         *ret_drv_mask = (*ret_drv_mask) | (0x1 << new_drv_id);
      }
   }

   return PM_ERR_FLAG_SUCCESS;
}
