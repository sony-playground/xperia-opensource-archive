/*! \file pm_target_information_init.c
*  
*  \brief This file contains functions to return target specific and common PMIC settings.
*  \n   
*  &copy; Copyright 2010-2017 QUALCOMM Technologies Incorporated, All Rights Reserved
*/

/*===========================================================================

                        EDIT HISTORY FOR MODULE

  This document is created by a code generator, therefore this section will
  not contain comments describing changes made to the module.

$Header: //components/rel/aop.ho/5.0/aop_proc/core/pmic/pm/framework/src/init/pm_target_information_init.c#1 $ 

when       who        	what, where, why
--------   ---    	   ----------------------------------------------------------
06/11/13    hs          Adding settling time for regulators.
06/04/13    aks         Remove range related hacks
05/29/13    aks         Clk driver input check (do not disable critical clocks)
05/29/13    kt          Added Peripheral Probe fix.
05/20/13    aks         Clk driver code re-architecture
04/23/13    hs          Fixed the naming convention in \config.
04/16/13    hs          Added workaround for 8110 L1.
04/12/13    hs          Code refactoring.
02/27/13    hs          Code refactoring.
08/07/12    hs          Added support for 5V boost.
04/16/12    hs          Removed irq files.
04/03/10    wra	        Creating file for MSM8960
========================================================================== */

/*===========================================================================

                     INCLUDE FILES 

===========================================================================*/
#include "pm_target_information.h"
#include "pm_version.h"
#include "pm_comm.h"
#include "device_info.h"
//#include "pm_prm_device_defs.h"

/*===========================================================================

                        STATIC/EXTERN VARIABLES 

===========================================================================*/


/*===========================================================================

                     FUNCTION DEFINITIONS

===========================================================================*/

__attribute__((section("rinit_code_sec_pool1")))
pm_err_flag_type pm_target_information_read_peripheral_rev(pm_comm_info_type *comm_ptr, peripheral_info_type *peripheral_info)
{
    pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
    pm_register_address_type base_address = (pm_register_address_type)peripheral_info->base_address;
    uint32 digital_minor_index = 0;
    uint32 digital_major_index = 1;
    uint32 analog_minor_index = 2;
    uint32 analog_major_index = 3;
    uint32 peripheral_type_index = 4;
    uint32 peripheral_subtype_index = 5;
    uint32 peripheral_dummy_index = 6;
    const uint32 num_of_bytes = 7;
    pm_register_data_type temp_peripheral_info[7] = {0};

    if(!comm_ptr)
    {
        return PM_ERR_FLAG_BUS_ERR;
    }

    // Reset the peripheral info
    peripheral_info->peripheral_type = 0;
    peripheral_info->peripheral_subtype = 0;
    peripheral_info->analog_major_version = 0;
    peripheral_info->analog_minor_version = 0;
    peripheral_info->digital_major_version = 0;
    peripheral_info->digital_minor_version = 0;

    /* Burst read the peripheral info */
    pm_comm_read_byte_array(comm_ptr->slave_id, base_address, num_of_bytes, temp_peripheral_info, 0);

    /* When we burst read multiple bytes from a non-existent peripheral, the data returned
       should be same on all the bytes so we need to do the below check and return error */
    if(temp_peripheral_info[peripheral_subtype_index] == temp_peripheral_info[peripheral_dummy_index]) 
    {
        return PM_ERR_FLAG_PERIPHERAL_ERR;
    }

    /* Valid peripheral type can never be 0 */   
    if(temp_peripheral_info[peripheral_type_index] == 0) 
    {
        return PM_ERR_FLAG_PERIPHERAL_ERR;
    }
    
    peripheral_info->peripheral_type = temp_peripheral_info[peripheral_type_index];    
    peripheral_info->peripheral_subtype = temp_peripheral_info[peripheral_subtype_index];
    peripheral_info->digital_major_version = temp_peripheral_info[digital_major_index];
    peripheral_info->digital_minor_version = temp_peripheral_info[digital_minor_index];
    peripheral_info->analog_major_version = temp_peripheral_info[analog_major_index];
    peripheral_info->analog_minor_version = temp_peripheral_info[analog_minor_index];
    
    return err_flag;
}
