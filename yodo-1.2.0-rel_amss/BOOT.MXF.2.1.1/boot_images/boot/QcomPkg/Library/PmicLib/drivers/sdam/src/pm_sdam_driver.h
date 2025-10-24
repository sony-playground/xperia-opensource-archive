#ifndef __PM_SDAM_DRIVER_H__
#define __PM_SDAM_DRIVER_H__

/*! \file pm_sdam_driver.h
*  \n
*  \brief PBS Client driver type definitions and init function prototype.
*  \n
*  \n &copy; Copyright 2018-2021 QUALCOMM Technologies Incorporated, All Rights Reserved
*/
/* =======================================================================
                                Edit History
This section contains comments describing changes made to this file.
Notice that changes are listed in reverse chronological order.

$Header: //components/rel/core.boot/6.1.1/QcomPkg/Library/PmicLib/drivers/sdam/src/pm_sdam_driver.h#1 $

$Author: pwbldsvc $
$DateTime: 2022/08/18 10:15:46 $
when       who     what, where, why
--------   ---     ----------------------------------------------------------
02/24/18   rl      Created.
========================================================================== */
/*===========================================================================

                     INCLUDE FILES

===========================================================================*/
#include "pm_target_information.h"
#include "DALSys.h"
#include "pm_sdam.h"
#include "pm_config_target.h"

/*===========================================================================

                        TYPE DEFINITIONS

===========================================================================*/
typedef struct
{
  pm_register_address_type  peripheral_offset;
  pm_register_address_type  mem_start;
  pm_register_address_type  trig_arg;
  pm_register_address_type  trig_busy_ret;
  pm_register_address_type  sdam_size;
  pm_register_address_type  trig_set;
  pm_register_address_type  trig_clr;
}pm_sdam_reg_info_type;

typedef struct
{
  /*Comm info*/
  pm_comm_info_type  *comm_ptr;

  /*Register Table*/
  pm_sdam_reg_info_type*  sdam_reg_table;

  /*Number of Peripherals*/
  uint8  num_of_periph;

  /*Array for size of memory on each peripheral*/
  uint32  *sdam_mem_size;

  pm_register_address_type  base_address;
  
  /*Dal Handle for Mutex*/
  DALSYSSyncHandle  sdam_dal_sync_handle;

  /*Store SDAM MOD Dig. Major and Minor Ver.*/
  uint8 dig_maj_min_ver;
}pm_sdam_data_type;

/*===========================================================================

                        FUNCTION PROTOTYPES

===========================================================================*/
void
pm_sdam_driver_init(pm_comm_info_type *comm_ptr,
                    peripheral_info_type *peripheral_info,
                    uint32 pmic_index);

pm_sdam_data_type* pm_sdam_get_data(uint32 pmic_index);

pm_err_flag_type pm_sdam_driver_self_init(void);


#endif /* __PM_SDAM_DRIVER_H__ */

