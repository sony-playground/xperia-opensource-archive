/*! \file pm_bob_driver_init.c 
*  \n
*  \brief This file contains BOB peripheral driver initialization during which the driver
*         driver data is stored.
*  \n  
*  \n &copy; Copyright 2016 - 2018 QUALCOMM Technologies Incorporated, All Rights Reserved
*/

/* =======================================================================
                             Edit History
  This section contains comments describing changes made to this file.
  Notice that changes are listed in reverse chronological order.

$Header: //components/rel/aop.ho/5.0/aop_proc/core/pmic/pm/drivers/bob/src/init/pm_bob_driver_init.c#3 $

when       who     what, where, why
--------   ---     ----------------------------------------------------------
12/22/15   al      Created
========================================================================== */
/*===========================================================================

                     INCLUDE FILES 

===========================================================================*/
#include "pm_bob_driver.h"
#include "pm_target_information.h"
#include "device_info.h"
#include "pm_debug.h"

/*===========================================================================

                        STATIC VARIABLES 

===========================================================================*/

#define BOB_AHC_CTL1_OFFSET  0x21

#define AHC_RESERVED_HR_SEL_MASK  0x70
#define AHC_EN_CTL_MASK  0x80
#define AHC_EPM_HW_STATUS 0x0D
#define AHC_PRESENT_MASK 0x10


static pm_pwr_register_info_type bob_reg = 
{
  .peripheral_offset     = 0x200,
  .STATUS                = 0x008,
  .INT_SET_TYPE          = 0x011,
  .INT_POLARITY_HIGH     = 0x012,
  .INT_POLARITY_LOW      = 0x013,
  .INT_LATCHED_CLR       = 0x014,
  .INT_EN_SET            = 0x015,
  .INT_EN_CLR            = 0x016,
  .VOLTAGE_CTRL1         = 0x040,
  .VOLTAGE_CTRL2         = 0x041,
  .VSET_VALID_LB         = 0x042,
  .VSET_VALID_UB         = 0x043,
  .MODE_CTL              = 0x045,
  .EN_CTL                = 0x046,
  .FOLLOW_HWEN           = 0x047,
  .SOFT_START_CTL        = 0x03B,
  .VOLTAGE_STEP_CTL      = 0x03C,
  .OCP                   = 0x088,
  .PMIC4_OCP             = 0x066,
  .ULS_VSET_LB           = 0x039,
  .PMIC4_ULS_VSET_LB     = 0x068,
  .SEC_ACCESS            = 0x0D0,
  .AHC_CTL               = 0x023,
};

/* extern global variable to store the BOB driver data */
 extern pm_bob_data_type *pm_bob_data_arr[PM_MAX_NUM_PMICS];

/*===========================================================================

                     INTERNAL DRIVER FUNCTIONS 

===========================================================================*/
__attribute__((section("rinit_code_sec_pool1")))
void pm_bob_driver_init(pm_comm_info_type * comm_ptr, peripheral_info_type * peripheral_info, uint8 pmic_index)
{
    pm_bob_data_type *bob_ptr = NULL;
    uint16 bob_index = 0;
    pm_register_address_type base_address = 0;
    pm_register_address_type periph_offset = 0;
    pm_register_address_type reg = 0;
    pm_err_flag_type err_flag;
    pm_register_data_type max_volt[2] = { 0 };
    boolean ahc_status = FALSE;
    boolean ahc_present = FALSE;
    uint8   data = 0;

    pm_debug_info_type *pmic_debug = pm_get_debug_info();
    CORE_VERIFY_PTR(pmic_debug);
    pmic_debug->pm_bob_data_arr = pm_bob_data_arr;

    if ((peripheral_info->peripheral_subtype == PM_HW_MODULE_BOB_MONITORING) ||
        (peripheral_info->peripheral_subtype == PM_HW_MODULE_BOB510_MONITORING) || 
        (peripheral_info->peripheral_subtype == PM_HW_MODULE_BOB520_MONITORING))
    {
        /*supports only BOB_CONFIG,BOB_510,BOB520*/
        return;
    }

    bob_ptr = pm_bob_data_arr[pmic_index];

    if (bob_ptr == NULL)
    {
        pm_malloc(sizeof(pm_bob_data_type), (void **)&bob_ptr);

        /* Assign Comm ptr */
        bob_ptr->comm_ptr = comm_ptr;

        /* BOB Register Info */
        bob_ptr->pm_pwr_data.pwr_reg_table = &bob_reg;
        bob_ptr->pm_pwr_data.base_address = peripheral_info->base_address;

        CORE_VERIFY_PTR(bob_ptr->pm_pwr_data.pwr_reg_table);

        /* BOB Num of peripherals - Obtaining Data through dal config */
        bob_ptr->pm_pwr_data.num_of_peripherals = pm_target_information_get_periph_count_info(PM_PROP_BOB_NUM, pmic_index);

        /* Num of peripherals cannot be 0 if this driver init gets called */
        CORE_VERIFY(bob_ptr->pm_pwr_data.num_of_peripherals != 0);

        /* BOB pwr rail specific info pointer malloc to save all the peripheral's base address, Type, Range and Vset */
        pm_malloc(sizeof(pm_pwr_specific_info_type) * (bob_ptr->pm_pwr_data.num_of_peripherals), (void **)&(bob_ptr->pm_pwr_data.pwr_specific_info));

        /* Save first BOB peripheral's base address */
        bob_ptr->pm_pwr_data.pwr_specific_info[0].periph_base_address = peripheral_info->base_address;

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

        if (peripheral_info->peripheral_subtype >= PM_HW_MODULE_BOB510_CONFIG)
        {
            bob_ptr->pm_pwr_data.pwr_specific_info[bob_index].pmic4_flag = FALSE;
        }
       else
        {
           bob_ptr->pm_pwr_data.pwr_specific_info[bob_index].pmic4_flag = TRUE;
        }

        /* Read current BOB's upper limit voltage value and save it */
	      reg = (pm_register_address_type)(peripheral_info->base_address + bob_ptr->pm_pwr_data.pwr_reg_table->PMIC4_ULS_VSET_LB);
        err_flag = pm_comm_read_byte_array(bob_ptr->comm_ptr->slave_id, reg, 2, max_volt, 0);
        CORE_VERIFY(err_flag == PM_ERR_FLAG_SUCCESS);

        /* BOB Vset Info - 1mV step for HT rails */
        bob_ptr->pm_pwr_data.pwr_specific_info[bob_index].pwr_vset.RangeMin = 0;
        bob_ptr->pm_pwr_data.pwr_specific_info[bob_index].pwr_vset.RangeMax = ((max_volt[1] << 8) | (max_volt[0])) * 1000;
        bob_ptr->pm_pwr_data.pwr_specific_info[bob_index].pwr_vset.VStep = 1000;
        bob_ptr->pm_pwr_data.pwr_specific_info[bob_index].is_periph_stepper = TRUE;

        /*check if ahc is present or not */
        if(peripheral_info->peripheral_subtype >= PM_HW_MODULE_BOB520_CONFIG)
        {
          reg = (pm_register_address_type)(peripheral_info->base_address + AHC_EPM_HW_STATUS);
          err_flag |= pm_comm_read_byte(bob_ptr->comm_ptr->slave_id, reg, &data , 0);
          ahc_present = (data & AHC_PRESENT_MASK) != 0 ? TRUE : FALSE;
        }
        
        if(ahc_present)
        {
          /* Store AHC Enablement Status */  
          reg = (pm_register_address_type)(peripheral_info->base_address + bob_ptr->pm_pwr_data.pwr_reg_table->AHC_CTL);
          err_flag |= pm_comm_read_byte(bob_ptr->comm_ptr->slave_id, reg, &data , 0);
          ahc_status = (data & AHC_EN_CTL_MASK) != 0 ? TRUE : FALSE;
          bob_ptr->pm_pwr_data.pwr_specific_info[bob_index].is_ahc_enabled = ahc_status;
        }

        if(ahc_status)
        {
          /* Get AHC Reserved HR */
          reg = (pm_register_address_type)(peripheral_info->base_address + BOB_AHC_CTL1_OFFSET);
          err_flag |= pm_comm_read_byte(bob_ptr->comm_ptr->slave_id, reg, &data, 0);
          bob_ptr->pm_pwr_data.pwr_specific_info[bob_index].ahc_reserved_hr = ((data & AHC_RESERVED_HR_SEL_MASK) >> 4) * 32;
        }
    }
} 

__attribute__((section("rinit_code_sec_pool1")))
uint8 pm_bob_get_num_peripherals(uint8 pmic_index)
{
    if((pmic_index < PM_MAX_NUM_PMICS) &&
       (pm_bob_data_arr[pmic_index] != NULL))
    {
        return pm_bob_data_arr[pmic_index]->pm_pwr_data.num_of_peripherals;
    }

    return NULL;
}
