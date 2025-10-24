#ifndef PM_PSTM_DRIVER__H
#define PM_PSTM_DRIVER__H

/*! \file pm_pstm_driver.h
 *  \n
 *  \brief This file contains SMPS peripheral driver related function prototypes,
 *         enums and driver data structure type.   
 *  \n  
 *  \n &copy; Copyright 2012-2020 QUALCOMM Technologies Incorporated, All Rights Reserved
 */

/* =======================================================================
                             Edit History
  This section contains comments describing changes made to this file.
  Notice that changes are listed in reverse chronological order.

  $Header: //components/rel/aop.ho/5.0/aop_proc/core/pmic/pm/drivers/pstm/src/pm_pstm_driver.h#1 $

when       who     what, where, why
--------   ---     ----------------------------------------------------------

========================================================================== */
/*===========================================================================

                     INCLUDE FILES 

===========================================================================*/
#include "pm_err_flags.h"
#include "pm_comm.h"

/*===========================================================================

                     SMPS TYPES AND STRUCTURES 

===========================================================================*/
typedef struct 
{ 
  pm_register_address_type    SW_ARG;             // Software Argument
  pm_register_address_type    PBS_ACK;            // PBS Acknowledgment
  pm_register_address_type    OFFSET;             // offset argument for future use
}pm_pstm_register_info_type;


typedef struct
{
  pm_comm_info_type           *comm_ptr;
  pm_register_address_type    base_address;
  uint32                      num_of_peripherals;
  pm_pstm_register_info_type  *pstm_reg_table;
} pm_pstm_data_type;

/*===========================================================================

                     FUNCTION DECLARATION 

===========================================================================*/
void pm_pstm_driver_init(pm_comm_info_type *comm_ptr, peripheral_info_type *peripheral_info, uint8 pmic_index);

pm_pstm_data_type* pm_pstm_get_data(uint8 pmic_index);
uint8 pm_pstm_get_num_peripherals(uint8 pmic_index);

#endif // PM_PSTM_DRIVER__H
