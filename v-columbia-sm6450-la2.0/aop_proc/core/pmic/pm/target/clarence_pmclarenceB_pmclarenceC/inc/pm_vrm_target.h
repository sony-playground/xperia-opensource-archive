#ifndef __PM_VRM_TARGET_H__
#define __PM_VRM_TARGET_H__

/*! \file pm_vrm_target.h
 *  \n
 *  \brief This file contains PMIC VRM TARGET specific resource related definitions.
 *  \n  
 *  \n &copy; Copyright 2016 QUALCOMM Technologies Incorporated, All Rights Reserved
 */

/* =======================================================================
                             Edit History
  This section contains comments describing changes made to this file.
  Notice that changes are listed in reverse chronological order.

$Header: //components/dev/aop.ho/4.0/tmajumde.aop.ho.4.0.05202022_clarence_build_support/aop_proc/core/pmic/pm/target/netrani_pmnetraniB_pmnetraniC/inc/pm_vrm_target.h#1 $  

when       who     what, where, why
--------   ---     ---------------------------------------------------------- 
02/06/17   kt     Created
===========================================================================*/

/*===========================================================================

                     INCLUDE FILES 

===========================================================================*/

#include "pm.h"

/*===========================================================================

                     TYPE DEFINITIONS/MACROS

===========================================================================*/



/*===========================================================================

                     FUNCTION DEFINITIONS

===========================================================================*/

//To rgister pre dependcency info for target specific resources
void pm_vrm_target_pre_register_resource_dependencies(void);

// Target specific resources that needs to be registered in VRM (example: pbs, gpio)
void pm_vrm_target_register_resources(void);

#endif //__PM_VRM_TARGET_H__


