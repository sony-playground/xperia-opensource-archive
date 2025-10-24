#ifndef __PM_VRM_H__
#define __PM_VRM_H__

/*! \file pm_vrm.h
 *  \n
 *  \brief This file contains PMIC VRM initialization related definitions.
 *  \n  
 *  \n &copy; Copyright 2016 QUALCOMM Technologies Incorporated, All Rights Reserved
 */

/* =======================================================================
                             Edit History
  This section contains comments describing changes made to this file.
  Notice that changes are listed in reverse chronological order.

$Header: //components/rel/aop.ho/5.0/aop_proc/core/pmic/pm/vrm/inc/pm_vrm.h#1 $  

when       who     what, where, why
--------   ---     ---------------------------------------------------------- 
08/29/16   kt     Created
===========================================================================*/

/*===========================================================================

                     INCLUDE FILES 

===========================================================================*/

#include "vrm_inc.h"
#include "pm_app_vrm.h"
#include "pm_vrm_vreg.h"
#include "pm_vrm_clk.h"
#include "pm_vrm_pstm.h"
#include "pm_vrm_target.h"
#include "pm_target_information.h"
#include "page_select.h"

/*===========================================================================

                     TYPE DEFINITIONS/MACROS

===========================================================================*/

#define PM_VREG_READY_IRQ_LATCHED_CLR_DATA 0x2
#define PM_STEPPER_DELAY_MASK 0x3

/*===========================================================================

                     FUNCTION DEFINITIONS

===========================================================================*/

void pm_vrm_init(void);
void pm_vrm_register_resources (void);
void pm_vrm_pre_register_resource_dependencies(uint8 pmic_index, pm_vrm_periph_type rsrc_type, uint32 num_rsrc);

pm_err_flag_type pm_vrm_get_drv_mask(uint32 drv_mask, uint32* ret_drv_mask);

#endif //__PM_VRM_H__


