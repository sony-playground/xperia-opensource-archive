#ifndef PM_ADC_CONFIG__H
#define PM_ADC_CONFIG__H

/*! \file
*  \n
*  \brief  pm_adc_config.h 
*  \details  This file contains functions prototypes and variable/type/constant
*  declarations for supporting ADC boot time configs
*  
*  \n &copy; Copyright 2019-2022 QUALCOMM Technologies Incorporated, All Rights Reserved
*/

/* =======================================================================
Edit History
This section contains comments describing changes made to this file.
Notice that changes are listed in reverse chronological order.


$Header: //components/rel/core.boot/6.1.1/QcomPkg/Library/PmicLib/target/kailua/system/src/pm_adc_config.h#1 $
$Author: pwbldsvc $
$DateTime: 2022/08/18 10:15:46 $
when         who     what, where, why
----------   ---     ----------------------------------------------------------
2019-11-15   rh      Initial creation
========================================================================== */

/*===========================================================================
                  INCLUDE FILES
===========================================================================*/

#include "pm_target_information.h"
#include "pm_err_flags.h"

/*===========================================================================

                     VIB TYPES AND STRUCTURES 

===========================================================================*/
typedef enum
{
   PM_ADC_CAL_NO_CAL = 0,
   PM_ADC_CAL_RATIO_CAL = 1,
   PM_ADC_CAL_ABX_CAL = 2
} pm_qbg_adc_cal_type;


typedef struct
{
    pm_qbg_adc_cal_type qbg_tbat_cal_fast_char;
    pm_qbg_adc_cal_type qbg_tbat_cal_xpm;
} pm_qbg_tbat_cal_specific_data_type;


// Use SDAM23_MEM125[0]: 1 -- factory has trimmed ext sns
#define EXT_RSNS_TRIM_FLAG_SID (PMIC_A)
#define EXT_RSNS_TRIM_FLAG_ADDR (0x86BD)
#define EXT_RSNS_TRIM_FLAG_MASK (PM_BIT(0))


/*===========================================================================

                     FUNCTION DECLARATION 

===========================================================================*/
pm_err_flag_type pm_ext_rsns_init();
pm_err_flag_type pm_qbg_tbat_cal_type_init();

#endif // PM_ADC_CONFIG__H

