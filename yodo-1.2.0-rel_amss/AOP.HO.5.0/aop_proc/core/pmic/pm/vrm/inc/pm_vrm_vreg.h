#ifndef __PM_VRM_VREG_H__
#define __PM_VRM_VREG_H__

/*! \file pm_vrm_vreg.h
 *  \n
 *  \brief This file contains PMIC VRM VREG related definitions.
 *  \n  
 *  \n &copy; Copyright 2016 - 2017 QUALCOMM Technologies Incorporated, All Rights Reserved
 */

/* =======================================================================
                             Edit History
  This section contains comments describing changes made to this file.
  Notice that changes are listed in reverse chronological order.

$Header: //components/rel/aop.ho/5.0/aop_proc/core/pmic/pm/vrm/inc/pm_vrm_vreg.h#1 $  

when       who     what, where, why
--------   ---     ---------------------------------------------------------- 
08/29/16   kt     Created
===========================================================================*/

/*===========================================================================

                     INCLUDE FILES 

===========================================================================*/

#include "pm.h"
#include "pm_smps_driver.h"
#include "pm_ldo_driver.h"
#include "pm_bob_driver.h"

/*===========================================================================

                     TYPE DEFINITIONS/MACROS

===========================================================================*/


/*===========================================================================

                     FUNCTION DEFINITIONS

===========================================================================*/

void pm_vrm_vreg_register_resources(uint8 pmic_index, pm_vrm_periph_type vreg_type, uint32 num_rails);


#endif //__PM_VRM_VREG_H__


