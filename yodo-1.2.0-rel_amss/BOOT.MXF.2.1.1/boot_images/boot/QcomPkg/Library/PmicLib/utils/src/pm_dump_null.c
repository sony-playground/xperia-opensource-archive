/*! \file  pm_dump_null.c
*  
*  \brief  pm_dump_null.c ----This file contain PMIC dump related API 
*  \details This file contain PMIC dump related API 
*  
*  &copy; Copyright 2020-2022 Qualcomm Technologies Incorporated, All Rights Reserved
*/

/*===========================================================================

EDIT HISTORY FOR MODULE

This document is created by a code generator, therefore this section will
not contain comments describing changes made to the module.


$Header: //components/rel/core.boot/6.1.1/QcomPkg/Library/PmicLib/utils/src/pm_dump_null.c#1 $
$Author: pwbldsvc $
$DateTime: 2022/08/18 10:15:46 $
when       who     what, where, why
--------   ---     ---------------------------------------------------------- 
07/20/21   zxz     Created

===========================================================================*/

/*===========================================================================

INCLUDE FILES 

===========================================================================*/
#include "pm_dump.h"
#include "pm_comm.h"
#include "pm_prop_ids.h"
#include "pm_utils.h"
#include "pm_resource_manager.h"
#include "pm_target_information.h"
#include "CoreVerify.h"


/*===========================================================================

                        GLOBALS and TYPE DEFINITIONS 

===========================================================================*/



/*===========================================================================

                        FUNCTION DEFINITIONS 

===========================================================================*/
pm_err_flag_type pm_dump_pbus_logger(uint8* buf, uint64 offset, uint64 size, uint64* dumped_size, boolean* complete)
{
  return PM_ERR_FLAG_SUCCESS;
}

pm_err_flag_type pm_pmic_dump_entry(uint8* buf, uint64 offset, uint64 size)
{
  return PM_ERR_FLAG_SUCCESS;
}

pm_err_flag_type pm_dump_pmic_register(uint8* buf, uint64 offset, uint64 size, uint64* dumped_size, boolean* complete)
{
  return PM_ERR_FLAG_SUCCESS;
}

