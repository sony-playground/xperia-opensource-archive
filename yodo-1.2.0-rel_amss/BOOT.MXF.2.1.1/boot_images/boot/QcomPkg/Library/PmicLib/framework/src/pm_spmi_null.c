/*! \file pm_spmi_null.c
*   \n
*   \brief This file contains PMIC access control null function
*   \n 
*   \n
*   \n &copy; Copyright 2010-2022 QUALCOMM Technologies Incorporated, All Rights Reserved
*/

/*===========================================================================

                        EDIT HISTORY FOR MODULE

  This document is created by a code generator, therefore this section will
  not contain comments describing changes made to the module.


$Header:  $
$Author: pwbldsvc $
$DateTime: 2022/02/22 18:53:09 $
when       who     what, where, why
--------   ---     ---------------------------------------------------------- 
05/27/22   cgoel     Created.
===========================================================================*/

/*===========================================================================

                     INCLUDE FILES 

===========================================================================*/
#include "pm_device.h"
#include "pm_err_flags.h"

/*===========================================================================

                        GLOBALS and TYPE DEFINITIONS 

===========================================================================*/
/*===========================================================================

                        FUNCTION DEFINITIONS 

===========================================================================*/
pm_err_flag_type 
pm_spmi_ac_cfg()
{
  return PM_ERR_FLAG_SUCCESS;
}
