/*! \file pm_pstm_driver_init.c 
*  \n
*  \brief This file contains pstm peripheral driver initialization during which the driver
*         driver data is stored. 
*  \n  
*  \n &copy; Copyright 2012-2020 QUALCOMM Technologies Incorporated, All Rights Reserved
*/

/* =======================================================================
                             Edit History
  This section contains comments describing changes made to this file.
  Notice that changes are listed in reverse chronological order.

$Header: //components/rel/aop.ho/5.0/aop_proc/core/pmic/pm/drivers/pstm/src/init/pm_pstm_driver_init.c#1 $

when       who     what, where, why
--------   ---     ----------------------------------------------------------

========================================================================== */
/*===========================================================================

                     INCLUDE FILES 

===========================================================================*/
#include "pm_pstm_driver.h"
#include "pm_target_information.h"
#include "pm_version.h"
#include "pm_comm.h"
#include "device_info.h"
#include "pm_debug.h"

/*===========================================================================

                        STATIC VARIABLES 

===========================================================================*/

static pm_pstm_register_info_type pstm_reg = 
{
  .SW_ARG      = 0x50,
  .PBS_ACK     = 0x51,
  .OFFSET      = 0x100, //future use
};

/* extern global variable to store the pstm driver data */
extern pm_pstm_data_type *pm_pstm_data_arr[PM_MAX_NUM_PMICS];

/*===========================================================================

                     FUNCTION DECLARATION 

===========================================================================*/

/*===========================================================================

                     INTERNAL DRIVER FUNCTIONS 

===========================================================================*/
__attribute__((section("rinit_code_sec_pool1")))
void pm_pstm_driver_init(pm_comm_info_type *comm_ptr, peripheral_info_type *peripheral_info, uint8 pmic_index)
{
  pm_pstm_data_type *pstm_ptr = NULL;
  uint16 pstm_index = 0;
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;

  pm_debug_info_type *pmic_debug = pm_get_debug_info();
  CORE_VERIFY_PTR(pmic_debug);
  pmic_debug->pm_pstm_data_arr = pm_pstm_data_arr;

  pstm_ptr = pm_pstm_data_arr[pmic_index];
  
  if (pstm_ptr == NULL)
  {
      pm_malloc( sizeof(pm_pstm_data_type), (void**)&pstm_ptr);
                                                  
      /* Assign Comm ptr */
      pstm_ptr->comm_ptr = comm_ptr;

      /* PSTM Register Info */
      pstm_ptr->pstm_reg_table = &pstm_reg;

      CORE_VERIFY_PTR(pstm_ptr->pstm_reg_table);

      pstm_ptr->base_address = peripheral_info->base_address;

      pm_pstm_data_arr[pmic_index] = pstm_ptr;
  }
  if (pstm_ptr != NULL)
  {
     pstm_ptr->num_of_peripherals +=1; //future use for multiple pstm/pmic
  }
}

__attribute__((section("rinit_code_sec_pool1")))
uint8 pm_pstm_get_num_peripherals(uint8 pmic_index)
{
  if((pmic_index < PM_MAX_NUM_PMICS) && 
      (pm_pstm_data_arr[pmic_index] != NULL))
  {
      return pm_pstm_data_arr[pmic_index]->num_of_peripherals;
  }

  return NULL;
}

