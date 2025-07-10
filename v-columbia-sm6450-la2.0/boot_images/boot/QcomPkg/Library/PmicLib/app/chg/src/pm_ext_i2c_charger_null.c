/*! \file
*  
*  \brief  pm_ext_i2c_charger_null.c, Null implement for pm_ext_i2c_charger.c
*    
*  &copy; Copyright 2022 QUALCOMM Technologies Incorporated, All Rights Reserved
*/

/*===========================================================================

EDIT HISTORY FOR MODULE

when       who     what, where, why
--------   ---     ----------------------------------------------------------
01/06/22   xp      Creation
===========================================================================*/

#include "pm_ext_i2c_charger.h"
#include "pm_err_flags.h"


pm_err_flag_type
pm_ext_i2c_charger_rerun_apsd(void)
{
  return PM_ERR_FLAG_SUCCESS;
}


