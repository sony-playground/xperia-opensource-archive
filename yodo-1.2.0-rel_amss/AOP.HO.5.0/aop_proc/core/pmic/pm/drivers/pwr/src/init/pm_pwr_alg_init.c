/*! \file pm_pwr_alg_init.c 
*  \n
*  \brief  
*  \n  
*  \n &copy; Copyright 2012-2018 QUALCOMM Technologies Incorporated, All Rights Reserved
*/

/* =======================================================================
                             Edit History
  This section contains comments describing changes made to this file.
  Notice that changes are listed in reverse chronological order.

$Header: //components/rel/aop.ho/5.0/aop_proc/core/pmic/pm/drivers/pwr/src/init/pm_pwr_alg_init.c#1 $

when        who     what, where, why
--------    ---     ----------------------------------------------------------
07/22/14   aks     Adding API to round off voltage
12/06/12   hw      Rearchitecturing module driver to peripheral driver
========================================================================== */
/*===========================================================================

                     INCLUDE FILES 

===========================================================================*/
#include "pm_pwr_alg.h"
#include "pm_comm.h"

/*===========================================================================

                     FUNCTION IMPLEMENTATION 

===========================================================================*/
__attribute__((section("rinit_code_sec_pool1")))
pm_err_flag_type pm_pwr_pin_ctrl_status_alg(pm_pwr_data_type *pwr_data, pm_comm_info_type *comm_ptr, uint32 peripheral_index, pm_on_off_type *on_off, uint8 *select_pin)
{
    pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
    pm_register_address_type reg = 0x0;
    pm_register_data_type data = 0;
    uint8 mask = 0x0F;

    if ((peripheral_index >= pwr_data->num_of_peripherals) || (pwr_data->pwr_specific_info[peripheral_index].periph_type == 0))
    {
        err_flag = PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
    }
    else
    {
        if(pwr_data->pwr_specific_info[peripheral_index].is_periph_unified_reg == TRUE)
        {
            reg = (pm_register_address_type)(pwr_data->pwr_specific_info[peripheral_index].periph_base_address + pwr_data->pwr_reg_table->FOLLOW_HWEN);
        }
        else 
        {   
            reg = (pm_register_address_type)(pwr_data->pwr_specific_info[peripheral_index].periph_base_address + pwr_data->pwr_reg_table->EN_CTL);
        }
        
        err_flag = pm_comm_read_byte(comm_ptr->slave_id, reg, &data, 0);
        if(err_flag != PM_ERR_FLAG_SUCCESS)
        {
            *on_off = PM_INVALID;
            return err_flag;
        }

        *select_pin = (uint8)(data & mask);

        if(*select_pin != 0)
        {
            *on_off = PM_ON;
        }
        else
        {
            *on_off = PM_OFF;
        }
    }

    return err_flag;
}



__attribute__((section("rinit_code_sec_pool1")))
pm_err_flag_type pm_pwr_irq_enable_alg(pm_pwr_data_type *pwr_data, pm_comm_info_type *comm_ptr, uint32 peripheral_index, pm_pwr_irq_type irq, boolean enable)
{
    pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;

    if ((peripheral_index >= pwr_data->num_of_peripherals) || (pwr_data->pwr_specific_info[peripheral_index].periph_type == 0))
    {
        err_flag = PM_ERR_FLAG_PERIPHERAL_ERR;
    }
    else if (irq >= PM_PWR_IRQ_INVALID)
    {
        err_flag = PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
    }
    else if (pwr_data->pwr_specific_info[peripheral_index].is_periph_unified_reg == FALSE)
    {
        err_flag = PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
    }
    else
    {
        pm_register_address_type reg = 0;
        uint8 irq_mask = 0;

        switch (irq)
        {
        case PM_PWR_IRQ_VREG_FAULT:
          irq_mask = 0x01;
          break;
        case PM_PWR_IRQ_VREG_READY:
          irq_mask = 0x02;
          break;
        default:
          // This check is already done so exec cannot reach here
          err_flag = PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
          break;
        }
         
        if (enable == TRUE)
        {
            reg = (pm_register_address_type)(pwr_data->pwr_specific_info[peripheral_index].periph_base_address + pwr_data->pwr_reg_table->INT_EN_SET);
        }
        else
        {
            reg = (pm_register_address_type)(pwr_data->pwr_specific_info[peripheral_index].periph_base_address + pwr_data->pwr_reg_table->INT_EN_CLR);
        }

        if (PM_ERR_FLAG_SUCCESS == err_flag)
        {
            err_flag = pm_comm_write_byte(comm_ptr->slave_id, reg, irq_mask, 0);
        }
    }

    return err_flag;
}

__attribute__((section("rinit_code_sec_pool1")))
pm_err_flag_type pm_pwr_irq_clear_alg(pm_pwr_data_type *pwr_data, pm_comm_info_type *comm_ptr, uint32 peripheral_index, pm_pwr_irq_type irq)
{
    pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;

    if ((peripheral_index >= pwr_data->num_of_peripherals) || (pwr_data->pwr_specific_info[peripheral_index].periph_type == 0))
    {
        err_flag = PM_ERR_FLAG_PERIPHERAL_ERR;
    }
    else if (irq >= PM_PWR_IRQ_INVALID)
    {
        err_flag = PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
    }
    else if (pwr_data->pwr_specific_info[peripheral_index].is_periph_unified_reg == FALSE)
    {
        err_flag = PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
    }
    else
    {
        pm_register_address_type reg = 0;
        uint8 irq_mask = 0;

        switch (irq)
        {
        case PM_PWR_IRQ_VREG_FAULT:
          irq_mask = 0x01;
          break;
        case PM_PWR_IRQ_VREG_READY:
          irq_mask = 0x02;
          break;
        default:
          // This check is already done so exec cannot reach here
          err_flag = PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
          break;
        }

        reg = (pm_register_address_type)(pwr_data->pwr_specific_info[peripheral_index].periph_base_address + pwr_data->pwr_reg_table->INT_LATCHED_CLR);

        if (PM_ERR_FLAG_SUCCESS == err_flag)
        {
            err_flag = pm_comm_write_byte(comm_ptr->slave_id, reg, irq_mask, 0);
        }
    }

    return err_flag;
}

__attribute__((section("rinit_code_sec_pool1")))
pm_err_flag_type pm_pwr_irq_set_trigger_alg(pm_pwr_data_type *pwr_data, pm_comm_info_type *comm_ptr, uint32 peripheral_index, pm_pwr_irq_type irq, pm_irq_trigger_type trigger)
{
    pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;

    if ((peripheral_index >= pwr_data->num_of_peripherals) || (pwr_data->pwr_specific_info[peripheral_index].periph_type == 0))
    {
        err_flag = PM_ERR_FLAG_PERIPHERAL_ERR;
    }
    else if ((irq >= PM_PWR_IRQ_INVALID) || (trigger >= PM_IRQ_TRIGGER_INVALID))
    {
        err_flag = PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
    }
    else if (pwr_data->pwr_specific_info[peripheral_index].is_periph_unified_reg == FALSE)
    {
        err_flag = PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
    }
    else
    {
        pm_register_address_type INT_SET_TYPE = (pm_register_address_type)(pwr_data->pwr_specific_info[peripheral_index].periph_base_address + pwr_data->pwr_reg_table->INT_SET_TYPE);
        pm_register_address_type INT_POLARITY_HIGH = (pm_register_address_type)(pwr_data->pwr_specific_info[peripheral_index].periph_base_address + pwr_data->pwr_reg_table->INT_POLARITY_HIGH);
        pm_register_address_type INT_POLARITY_LOW = (pm_register_address_type)(pwr_data->pwr_specific_info[peripheral_index].periph_base_address + pwr_data->pwr_reg_table->INT_POLARITY_LOW);
        uint8 irq_mask = 0;
        uint8 set_type = 0;
        uint8 polarity_high = 0;
        uint8 polarity_low = 0;

        switch (irq)
        {
        case PM_PWR_IRQ_VREG_FAULT:
          irq_mask = 0x01;
          break;
        case PM_PWR_IRQ_VREG_READY:
          irq_mask = 0x02;
          break;
        default:
          // This check is already done so exec cannot reach here
          err_flag = PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
          break;
        }

        switch (trigger)
        {
        case PM_IRQ_TRIGGER_ACTIVE_LOW:
          set_type = 0x00;
          polarity_high = 0x00;
          polarity_low = 0xFF;
          break;
        case PM_IRQ_TRIGGER_ACTIVE_HIGH:
          set_type = 0x00;
          polarity_high = 0xFF;
          polarity_low = 0x00;
          break;
        case PM_IRQ_TRIGGER_RISING_EDGE:
          set_type = 0xFF;
          polarity_high = 0xFF;
          polarity_low = 0x00;
          break;
        case PM_IRQ_TRIGGER_FALLING_EDGE:
          set_type = 0xFF;
          polarity_high = 0x00;
          polarity_low = 0xFF;
          break;
        case PM_IRQ_TRIGGER_DUAL_EDGE:
          set_type = 0xFF;
          polarity_high = 0xFF;
          polarity_low = 0xFF;
          break;
        default:
          // This check is already done so exec cannot reach here
          err_flag = PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
          break;
        }

        if (PM_ERR_FLAG_SUCCESS == err_flag)
        {
            err_flag = pm_comm_write_byte_mask(comm_ptr->slave_id, INT_SET_TYPE, irq_mask, set_type, 0);
            err_flag |= pm_comm_write_byte_mask(comm_ptr->slave_id, INT_POLARITY_HIGH, irq_mask, polarity_high, 0);
            err_flag |= pm_comm_write_byte_mask(comm_ptr->slave_id, INT_POLARITY_LOW, irq_mask, polarity_low, 0);
        }
    }

    return err_flag;
}

__attribute__((section("rinit_code_sec_pool1")))
pm_err_flag_type
pm_pwr_ahc_en_status_alg ( pm_pwr_data_type  *pwr_data,
                           pm_comm_info_type *comm_ptr,
                           uint8 peripheral_index,
                           boolean *status)
{
    pm_register_address_type  reg       = 0xFF;
    uint8                     data      = 0;
    pm_err_flag_type          err_flag  = PM_ERR_FLAG_SUCCESS;
   
    if ((peripheral_index >= pwr_data->num_of_peripherals) ||
        (pwr_data->pwr_specific_info[peripheral_index].periph_type == 0))
    {
        return err_flag = PM_ERR_FLAG_INVALID_PERIPHERAL;
    }

    if (status == NULL)
    {
        return err_flag = PM_ERR_FLAG_INVALID_PARAMETER;
    }

    reg = (pm_register_address_type)
    (pwr_data->pwr_specific_info[peripheral_index].periph_base_address +
    pwr_data->pwr_reg_table->AHC_CTL);

    err_flag = pm_comm_read_byte_mask(comm_ptr->slave_id, reg, 0x80, &data, 0);

    *status = data == 0x80 ? TRUE : FALSE;

    return err_flag;
}

__attribute__((section("rinit_code_sec_pool1")))
pm_err_flag_type
pm_pwr_pbs_vote_en_status_alg ( pm_pwr_data_type  *pwr_data,
                                pm_comm_info_type *comm_ptr,
                                uint8 peripheral_index,
                                boolean *status)
{
    pm_register_address_type  reg       = 0x0;
    uint8                     data      = 0;
    pm_err_flag_type          err_flag  = PM_ERR_FLAG_SUCCESS;
   
    if ((peripheral_index >= pwr_data->num_of_peripherals) ||
        (pwr_data->pwr_specific_info[peripheral_index].periph_type == 0))
    {
        return err_flag = PM_ERR_FLAG_INVALID_PERIPHERAL;
    }

    if (status == NULL)
    {
        return err_flag = PM_ERR_FLAG_INVALID_PARAMETER;
    }

    reg = (pm_register_address_type)
    (pwr_data->pwr_specific_info[peripheral_index].periph_base_address +
    pwr_data->pwr_reg_table->PBS_VOTE_CTL);

    err_flag = pm_comm_read_byte_mask(comm_ptr->slave_id, reg, 0x80, &data, 0);

    *status = data == 0x80 ? TRUE : FALSE;

    return err_flag;
}