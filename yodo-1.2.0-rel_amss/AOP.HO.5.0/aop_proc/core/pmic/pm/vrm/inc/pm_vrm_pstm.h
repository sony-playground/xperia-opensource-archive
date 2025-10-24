#ifndef PM_VRM_PSTM_H
#define PM_VRM_PSTM_H

/*! \file pm_vrm_pstm.h
 *  \n
 *  \brief This file contains PMIC VRM PSTM related definitions.
 *  \n  
 *  \n &copy; Copyright 2020 QUALCOMM Technologies Incorporated, All Rights Reserved
 */

/* =======================================================================
                             Edit History
  This section contains comments describing changes made to this file.
  Notice that changes are listed in reverse chronological order.

$Header: //components/rel/aop.ho/5.0/aop_proc/core/pmic/pm/vrm/inc/pm_vrm_pstm.h#1 $  

when       who     what, where, why
--------   ---     ---------------------------------------------------------- 

===========================================================================*/

/*===========================================================================

                     INCLUDE FILES 

===========================================================================*/

#include "pm.h"
#include "pm_pstm_driver.h"

/*===========================================================================

                     TYPE DEFINITIONS/MACROS

===========================================================================*/



/*===========================================================================

                     FUNCTION DEFINITIONS

===========================================================================*/

//configuring the pstm related resources in VRM
void pm_vrm_pstm_register_resources(uint8 pmic_index, pm_vrm_periph_type pstm_type, uint32 num_pstm);


#endif //PM_VRM_PSTM_H


