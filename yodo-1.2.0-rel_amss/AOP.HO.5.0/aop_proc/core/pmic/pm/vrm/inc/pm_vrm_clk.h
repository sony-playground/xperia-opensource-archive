#ifndef PM_VRM_CLK_H
#define PM_VRM_CLK_H

/*! \file pm_vrm_clk.h
 *  \n
 *  \brief This file contains PMIC VRM CLK related definitions.
 *  \n  
 *  \n &copy; Copyright 2016 QUALCOMM Technologies Incorporated, All Rights Reserved
 */

/* =======================================================================
                             Edit History
  This section contains comments describing changes made to this file.
  Notice that changes are listed in reverse chronological order.

$Header: //components/rel/aop.ho/5.0/aop_proc/core/pmic/pm/vrm/inc/pm_vrm_clk.h#1 $  

when       who     what, where, why
--------   ---     ---------------------------------------------------------- 
08/29/16   kt     Created
===========================================================================*/

/*===========================================================================

                     INCLUDE FILES 

===========================================================================*/

#include "pm.h"
#include "pm_clk_driver.h"

/*===========================================================================

                     TYPE DEFINITIONS/MACROS

===========================================================================*/


/*===========================================================================

                     FUNCTION DEFINITIONS

===========================================================================*/

void pm_vrm_clk_register_resources(uint8 pmic_index, pm_vrm_periph_type clk_type, uint32 num_clks);


#endif //PM_VRM_CLK_H


