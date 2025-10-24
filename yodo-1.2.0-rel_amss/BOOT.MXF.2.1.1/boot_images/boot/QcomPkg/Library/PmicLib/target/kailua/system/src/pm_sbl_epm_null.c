/*! \file pm_sbl_epm_null.c
*  \n
*  \brief This file contains PMIC EPM related functions
*  \n
*  \n &copy; Copyright 2022 QUALCOMM Technologies Incorporated, All Rights Reserved
*/
/* =======================================================================
Edit History
This section contains comments describing changes made to this file.
Notice that changes are listed in reverse chronological order.


$Header: $
$Author:  $
$DateTime: $
when       who     what, where, why
--------   ---     ----------------------------------------------------------
07/19/22   al     new file
========================================================================== */
/*===========================================================================

                     INCLUDE FILES 

===========================================================================*/

#include "pm_sbl_boot_target.h"

/*===========================================================================

                        TYPE DEFINITIONS 

===========================================================================*/


pm_err_flag_type 
pm_sbl_epm_en( uint8 value)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;  
  
  return err_flag;
}
  
pm_err_flag_type 
pm_sbl_epm_mode( uint8 value)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;  
  
  return err_flag; 
}
  
pm_err_flag_type 
pm_sbl_epm_config(uint8 buck_en, uint8 buck_gang, uint8 buck_sid, uint8 buck_pid)
{ 
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS; 
    
  return err_flag;
}


