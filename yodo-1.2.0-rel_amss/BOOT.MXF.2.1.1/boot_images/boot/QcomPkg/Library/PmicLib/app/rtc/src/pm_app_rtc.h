/*! \file
*  
*  \brief  pm_app_rtc.h
*  \details Implementation file for rtc resourece type.
*
*  &copy; Copyright 2022 QUALCOMM Technologies Incorporated, All Rights Reserved
*/

/*===========================================================================

EDIT HISTORY FOR MODULE

This document is created by a code generator, therefore this section will
not contain comments describing changes made to the module.


$Header: //components/rel/core.boot/6.1.1/QcomPkg/Library/PmicLib/app/rtc/src/pm_app_rtc.h#1 $
$Author: pwbldsvc $
$DateTime: 2022/08/18 10:15:46 $
when        who     what, where, why
--------    ---     ---------------------------------------------------------- 
01/16/2022  dv      Initial app layer developement for RTC
===========================================================================*/

/*===========================================================================

                     INCLUDE FILES 

===========================================================================*/

#include "pm_err_flags.h"
#include "com_dtypes.h"
/*===========================================================================
FUNCTION  pm_app_rtc_get_rtc_status                      EXTERNAL FUNCTION

DESCRIPTION
This function gets the RTC reset status

PARAMETERS
None

RETURN VALUE
Type: pm_err_flag_type
- Possible values:
- PM_ERR_FLAG_SUCCESS               -> Operation succeeded.
- PM_ERR_FLAG_INVALID_PARAMETER     -> NULL pointer provided for reset_status.
- PM_ERR_FLAG_FEATURE_NOT_SUPPORTED -> Feature not available on this
version of the PMIC.
- PM_ERR_FLAG_BUS_ERR           	-> Communication with PM chip failed.
===========================================================================*/
pm_err_flag_type 
pm_app_rtc_update_status(void);
