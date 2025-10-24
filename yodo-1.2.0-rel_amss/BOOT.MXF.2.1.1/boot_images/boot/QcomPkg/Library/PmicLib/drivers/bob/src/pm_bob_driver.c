/*! \file pm_bob_driver.c 
*  \n
*  \brief This file contains BOB peripheral driver initialization during which the driver
*         driver data is stored.
*  \n  
*  \n &copy; Copyright 2016-2022 QUALCOMM Technologies Incorporated, All Rights Reserved
*/

/* =======================================================================
                             Edit History
  This section contains comments describing changes made to this file.
  Notice that changes are listed in reverse chronological order.

$Header: //components/rel/core.boot/6.1.1/QcomPkg/Library/PmicLib/drivers/bob/src/pm_bob_driver.c#1 $

$Author: pwbldsvc $
$DateTime: 2022/08/18 10:15:46 $
when       who     what, where, why
--------   ---     ----------------------------------------------------------
12/08/17   aab     Updated for pm_sw_mode_type change 
11/12/17   aab     Moved common Register address defination to driver file 
01/16/17   aab     Adapted it for SDM845 
12/22/15   al      Created
========================================================================== */
/*===========================================================================

                     INCLUDE FILES 

===========================================================================*/
#include "pm_bob_driver.h"
#include "pm_target_information.h"

/*===========================================================================

                        MACRO AND TYPE DEFINTIONS 

===========================================================================*/
#define PMIC_BOB_CONFIG_MAX_HW_VER 0x01

/*===========================================================================

                        STATIC VARIABLES 

===========================================================================*/

/* Static global variable to store the BOB driver data */
static pm_bob_data_type *pm_bob_data_arr[PM_MAX_NUM_PMICS];

static pm_pwr_register_info_type bob_reg =
{
   .peripheral_offset = 0x200,
   .STATUS            = 0x08,
   .STATUS3           = 0x0A,
   .STATUS4           = 0x0B,
   .ULS_VSET_LB       = 0x68,
   .AHC_CTL           = 0x0D,
   .VOLTAGE_CTRL1     = 0x00,
   .VOLTAGE_CTRL2     = 0x00, 
   .VSET_VALID_LB     = 0x42,
   .VSET_VALID_UB     = 0x43,
   .MODE_CTL          = 0x45,
   .EN_CTL            = 0x46,
   .FOLLOW_HWEN       = 0x37,
   .CLK_DIV           = 0x00,
   .QM_MODE           = 0x00,
   .QM_PS_ENTRY       = 0x00,
   .PMIC4_ULS_VSET_LB = 0x00,
   .QM_PS_EXIT        = 0x00,
   .OCP               = 0x4A, // Previously this is register offset for OCP before broadcast cfg
   .PD_CTL            = 0x48,
   .BROADCAST_CFG     = 0x8B,
   .GANG_CTL1         = 0x00,
   .ECM_EN_CTL        = 0x00,
   .VOUT_EXT_CTRL1_LB = 0x4A,
   .RGB_HR_VOUT_MAX   = 0x6E, 
};


/*===========================================================================

                     INTERNAL DRIVER FUNCTIONS 

===========================================================================*/

void pm_bob_driver_init(pm_comm_info_type * comm_ptr, peripheral_info_type * peripheral_info, uint8 pmic_index)
{
    pm_bob_data_type *bob_ptr = NULL;
    uint16 bob_index = 0;
    pm_register_address_type base_address = 0;
    pm_register_address_type periph_offset = 0;
    pm_register_data_type max_volt[2] = { 0 };
    pm_register_address_type reg = 0;
    uint8 step_size = 0x1;
    pm_err_flag_type err_flag;
    uint8 num_of_peripherals = 0;
    
    if ((peripheral_info->peripheral_subtype == PM_HW_MODULE_BOB_MONITORING)||
        (peripheral_info->peripheral_subtype == PM_HW_MODULE_BOB510_MONITORING) ||
		(peripheral_info->peripheral_subtype == PM_HW_MODULE_BOB_MONITORING_PERIPH))
    {
        /*supports only BOB_CONFIG*/
        return;
    }

    if (((peripheral_info->digital_major_version << 4) | peripheral_info->digital_minor_version) > PMIC_BOB_CONFIG_MAX_HW_VER)
    {
      CORE_VERIFY(0);
    }

    bob_ptr = pm_bob_data_arr[pmic_index];

    if (bob_ptr == NULL)
    {
        /* BOB Num of peripherals - Obtaining Data through dal config */
        num_of_peripherals = pm_target_information_get_periph_count_info(PM_PROP_BOB_NUM, pmic_index);
        if (num_of_peripherals == 0)
        {
            return;
        }

        pm_malloc(sizeof(pm_bob_data_type), (void **)&bob_ptr);

        /* Assign Comm ptr */
        bob_ptr->comm_ptr = comm_ptr;

        bob_ptr->pm_pwr_data.pwr_reg_table = &bob_reg;

        CORE_VERIFY_PTR(bob_ptr->pm_pwr_data.pwr_reg_table);

        bob_ptr->pm_pwr_data.base_address = peripheral_info->base_address; 

        bob_ptr->pm_pwr_data.num_of_peripherals = num_of_peripherals;

        /* BOB pwr rail specific info pointer malloc to save all the peripheral's base address, Type, Range and Vset */
        pm_malloc(sizeof(pm_pwr_specific_info_type) * (bob_ptr->pm_pwr_data.num_of_peripherals), (void **)&(bob_ptr->pm_pwr_data.pwr_specific_info));

        /* Save first BOB peripheral's base address */
        bob_ptr->pm_pwr_data.pwr_specific_info[0].periph_base_address = peripheral_info->base_address;
		
		/* BoB Subtype pointer malloc */
        pm_malloc(sizeof(uint8)*(bob_ptr->pm_pwr_data.num_of_peripherals), (void**)&(bob_ptr->periph_subtype));
		
		bob_ptr->periph_subtype[0] = peripheral_info->peripheral_subtype;

        pm_bob_data_arr[pmic_index] = bob_ptr;
    }

    if (bob_ptr != NULL)
    {
        base_address = bob_ptr->pm_pwr_data.pwr_specific_info[0].periph_base_address;
        periph_offset = bob_ptr->pm_pwr_data.pwr_reg_table->peripheral_offset;

        /* Peripheral Baseaddress should be >= first peripheral's base addr */
        CORE_VERIFY(peripheral_info->base_address >= base_address);

        /* Calculate BOB peripheral index */
        bob_index = ((peripheral_info->base_address - base_address) / periph_offset);

        /* Peripheral Index should be less than number of peripherals */
        CORE_VERIFY(bob_index < (bob_ptr->pm_pwr_data.num_of_peripherals));

        /* Save BOB's Peripheral Type value */
        bob_ptr->pm_pwr_data.pwr_specific_info[bob_index].periph_type = peripheral_info->peripheral_type;

        /* Save each BOB peripheral's base address */
        bob_ptr->pm_pwr_data.pwr_specific_info[bob_index].periph_base_address = peripheral_info->base_address;

        /* Flag this rail peripheral as unified register map peripheral */
        bob_ptr->pm_pwr_data.pwr_specific_info[bob_index].is_periph_unified_reg = TRUE;
		
		/* Save BoB's Peripheral Subtype value */
        bob_ptr->periph_subtype[bob_index] = peripheral_info->peripheral_subtype;

        /* Read current BOB's upper limit voltage value and save it */
        reg = (pm_register_address_type)(peripheral_info->base_address + bob_ptr->pm_pwr_data.pwr_reg_table->ULS_VSET_LB);
        if (peripheral_info->digital_major_version >= 2)
        {
            err_flag = pm_comm_read_byte_array(bob_ptr->comm_ptr->slave_id, reg, 2, max_volt);
            step_size = 1;
        }
        else
        {
            err_flag = pm_comm_read_byte(bob_ptr->comm_ptr->slave_id, reg, &max_volt[0]);
            max_volt[1] = 0x0; //for V1 targets, only lower byte is valid
            step_size = 32;
        }
        CORE_VERIFY(err_flag == PM_ERR_FLAG_SUCCESS);

        pm_malloc(sizeof(pm_pwr_volt_info_type), (void **)&(bob_ptr->pm_pwr_data.pwr_specific_info[bob_index].pwr_vset));

        /* BOB Vset Info - 1mV step for HT rails */
        bob_ptr->pm_pwr_data.pwr_specific_info[bob_index].pwr_vset.RangeMin = 0;
        bob_ptr->pm_pwr_data.pwr_specific_info[bob_index].pwr_vset.RangeMax = ((max_volt[1] << 8) | (max_volt[0])) * step_size * 1000;
        bob_ptr->pm_pwr_data.pwr_specific_info[bob_index].pwr_vset.VStep = 1000;
        bob_ptr->pm_pwr_data.pwr_specific_info[bob_index].is_periph_stepper = TRUE;
    }
} 

pm_bob_data_type* pm_bob_get_data(uint8 pmic_index)
{
    if(pmic_index < PM_MAX_NUM_PMICS)
    {
        return pm_bob_data_arr[pmic_index];
    }

    return NULL;
}

uint8 pm_bob_get_num_peripherals(uint8 pmic_index)
{
    if((pmic_index < PM_MAX_NUM_PMICS) &&
       (pm_bob_data_arr[pmic_index] != NULL))
    {
        return pm_bob_data_arr[pmic_index]->pm_pwr_data.num_of_peripherals;
    }

    return 0;
}

