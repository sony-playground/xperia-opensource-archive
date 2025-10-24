/*! \file
*  
*  \brief  pm_app_rtc.c
*  \details Implementation file for rtc resourece type.
*
*  &copy; Copyright 2022 QUALCOMM Technologies Incorporated, All Rights Reserved
*/

/*===========================================================================

EDIT HISTORY FOR MODULE

This document is created by a code generator, therefore this section will
not contain comments describing changes made to the module.


$Header: //components/rel/core.boot/6.1.1/QcomPkg/Library/PmicLib/app/rtc/src/pm_app_rtc.c#1 $
$Author: pwbldsvc $
$DateTime: 2022/08/18 10:15:46 $
when        who     what, where, why
--------    ---     ---------------------------------------------------------- 
01/06/2022  dv      Initial app layer developement for RTC
===========================================================================*/

/*===========================================================================

                     INCLUDE FILES 

===========================================================================*/

#include "pm_err_flags.h"
#include "pm_rtc.h"
#include "pm_rtc_driver.h"
#include "pm_sdam.h"

#define SDAM_MEM_007            0x07

pm_err_flag_type 
pm_app_rtc_update_status( void )
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  boolean status = FALSE;
  
  err_flag = pm_rtc_reset_status(PMIC_A, &status);

  if ((err_flag == PM_ERR_FLAG_SUCCESS) && status)
  {
    err_flag |= pm_sdam_mem_write (PMIC_A, PM_SDAM_4, SDAM_MEM_007, 1, &status);
    err_flag |= pm_rtc_clear_reset_status(PMIC_A);
  }

  return err_flag;
}

