#ifndef __UT_PM_COINCELL_H__
#define __UT_PM_COINCELL_H__
/*! \file ut_pm_coincell.h
 *  \n
 *  \brief This file contains functions and variable declarations to support 
 *   the testing Coincell driver module.
 *
 *  \n &copy; Copyright (c) 2022 by Qualcomm Technologies Inc.  All Rights Reserved.
 */

/*===========================================================================

                        EDIT HISTORY FOR MODULE

  This section contains comments describing changes made to the module.
  Notice that changes are listed in reverse chronological order.


when       who     what, where, why
--------   ---     ----------------------------------------------------------
09/02/22   gan      Created Coincell API.
===========================================================================*/
/*===========================================================================

                        HEADER FILES

===========================================================================*/
#include "pm_err_flags.h"
#include "com_dtypes.h"

/*===========================================================================

                        TYPE DEFINITIONS 

===========================================================================*/

/*Test API to call the COINCELL APIs for basic sanity testing*/
pm_err_flag_type coincell_test(void);

#endif // __UT_PM_COINCELL_H__
