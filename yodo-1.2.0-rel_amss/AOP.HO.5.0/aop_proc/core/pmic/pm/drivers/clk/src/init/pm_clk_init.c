/*! \file pm_clk_init.c
 *  \n
 *  \brief Implementation file for CLOCK public APIs. 
 *  \n  
 *  \n &copy; Copyright 2013-2016 QUALCOMM Technologies Incorporated, All Rights Reserved
 */

/* =======================================================================
                             Edit History
  This section contains comments describing changes made to this file.
  Notice that changes are listed in reverse chronological order.

$Header: //components/rel/aop.ho/5.0/aop_proc/core/pmic/pm/drivers/clk/src/init/pm_clk_init.c#2 $
 
when        who     what, where, why
--------    ---     ----------------------------------------------------------
08/12/13    aks      Fix KW Errors   
04/12/13    aks      Created as part of Code refactoring.
========================================================================== */
/*===========================================================================

                     INCLUDE FILES 

===========================================================================*/
#include "pm_clk_driver.h"
#include "pm_comm.h"

/*===========================================================================

                     API IMPLEMENTATION 

===========================================================================*/
__attribute__((section("rinit_code_sec_pool1")))
pm_err_flag_type pm_clk_sw_enable(uint8 pmic_chip, pm_clk_type periph, pm_on_off_type on_off)
{
    pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
    pm_clk_data_type *clk_ptr = pm_clk_get_data(pmic_chip);
    pm_register_address_type reg = 0;
    pm_register_data_type data = 0;
    uint32 periph_index = 0;

    if ((clk_ptr == NULL) || (periph >= PM_CLK_MAX_INDEX))
    {
        err_flag = PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
    }
    else
    {
        periph_index = clk_ptr->clk_perph_index[periph];

        if((periph_index == PM_CLK_INVALID_DATA) || (periph_index >= PM_MAX_NUM_CLKS) || 
           (clk_ptr->periph_subtype[periph_index] == 0))
        {
            err_flag = PM_ERR_FLAG_PERIPHERAL_ERR;
        }
        else
        {
            reg = clk_ptr->base_address + (pm_register_address_type)(clk_ptr->clk_reg_table->peripheral_offset*periph_index) + 
                  clk_ptr->clk_reg_table->EN_CTL;

            if (PM_ON == on_off)
            {
                data = 0xFF;
            }
            else
            {
                data = 0x00;
            }

            err_flag = pm_comm_write_byte_mask(clk_ptr->comm_ptr->slave_id, reg , 0x80, data, 0); // 7
        }
    }

    return err_flag;
}

__attribute__((section("rinit_code_sec_pool1")))
pm_err_flag_type pm_clk_get_warmup_time(uint8 pmic_chip, pm_clk_type periph, uint32 *warmup_time_usec)
{
    pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
    pm_clk_data_type *clk_ptr = pm_clk_get_data(pmic_chip);
    pm_register_address_type reg = 0, reg_xo = 0;
    pm_register_data_type data = 0, xo_data = 0;
    uint32 periph_index = 0;
    uint32 num_sleep_clk_cycles = 0;

    if ((clk_ptr == NULL) || (periph >= PM_CLK_MAX_INDEX))
    {
        err_flag = PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
    }
    else if (warmup_time_usec == NULL)
    {
        err_flag = PM_ERR_FLAG_INVALID_PARAMETER;
    }
    else
    {
        periph_index = clk_ptr->clk_perph_index[periph];

        if((periph_index == PM_CLK_INVALID_DATA) || (periph_index >= PM_MAX_NUM_CLKS) || 
           (clk_ptr->periph_subtype[periph_index] == 0))
        {
            err_flag = PM_ERR_FLAG_PERIPHERAL_ERR;
        }
        else
        {
            reg = clk_ptr->base_address + (pm_register_address_type)(clk_ptr->clk_reg_table->peripheral_offset*periph_index) + 
                  clk_ptr->clk_reg_table->TIMER;

            reg_xo = clk_ptr->base_address + clk_ptr->clk_reg_table->TIMER;
                  
            if ((clk_ptr->periph_subtype[periph_index] == PM_HW_MODULE_CLOCK_XO_CORE_38P4MHZ) ||
                (clk_ptr->periph_subtype[periph_index] == PM_HW_MODULE_CLOCK_BB_CLK) ||
                (clk_ptr->periph_subtype[periph_index] == PM_HW_MODULE_CLOCK_RF_CLK))
            {
                err_flag = pm_comm_read_byte(clk_ptr->comm_ptr->slave_id, reg, &data, 0);
                err_flag = pm_comm_read_byte(clk_ptr->comm_ptr->slave_id, reg_xo, &xo_data, 0);

                /* Delay time configured is twice the number of sleep (32kHz) clock cycles obtained from timer register */
                /* If child clock then add xo enable delay, for parent clock xo_data will be zero */
                if(clk_ptr->xo_always_on) //For parent clock pmic buffers
                {
                    num_sleep_clk_cycles = (uint32)((data * 2) + 3);
                }
                else //For child clock pmic buffers 
                {
                    num_sleep_clk_cycles = (uint32)( ((xo_data * 2) + 4) + ((data * 2) + 3)  );
                }
                
                *warmup_time_usec = (num_sleep_clk_cycles * 1000)/32;
            }
            else
            {
                err_flag = PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
            }
        }
    }

    return err_flag;
}

__attribute__((section("rinit_code_sec_pool1")))
pm_err_flag_type pm_clk_irq_enable(uint8 pmic_chip, pm_clk_type periph, pm_on_off_type on_off)
{
    pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
    pm_clk_data_type *clk_ptr = pm_clk_get_data(pmic_chip);
    pm_register_address_type reg = 0;
    pm_register_data_type en_mask = 0x02;
    pm_register_data_type data = 0;
    uint32 periph_index = 0;

    if ((clk_ptr == NULL) || (periph >= PM_CLK_MAX_INDEX))
    {
        err_flag = PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
    }
    else
    {
        periph_index = clk_ptr->clk_perph_index[periph];

        if ((periph_index == PM_CLK_INVALID_DATA) || (periph_index >= PM_MAX_NUM_CLKS) || (clk_ptr->periph_subtype[periph_index] == 0))
        {
           err_flag = PM_ERR_FLAG_PERIPHERAL_ERR;
        }
        else
        {
             if (PM_ON == on_off)
            {         
                reg = clk_ptr->base_address + (pm_register_address_type)(clk_ptr->clk_reg_table->peripheral_offset*periph_index) + 
                clk_ptr->clk_reg_table->INT_EN_SET;

                //enable the interrupt
                err_flag = pm_comm_write_byte(clk_ptr->comm_ptr->slave_id, reg, en_mask, 0);
            }
            else
            {
                reg = clk_ptr->base_address + (pm_register_address_type)(clk_ptr->clk_reg_table->peripheral_offset*periph_index) + 
                clk_ptr->clk_reg_table->INT_EN_CLR;

                //disable the interrupt
                err_flag = pm_comm_write_byte(clk_ptr->comm_ptr->slave_id, reg, en_mask, 0);
            }
        }
    }
    return err_flag;
}
