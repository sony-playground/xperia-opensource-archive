/*! \file pm_clk.c
 *  \n
 *  \brief Implementation file for CLOCK public APIs. 
 *  \n  
 *  \n &copy; Copyright 2013-2016 QUALCOMM Technologies Incorporated, All Rights Reserved
 */

/* =======================================================================
                             Edit History
  This section contains comments describing changes made to this file.
  Notice that changes are listed in reverse chronological order.

$Header: //components/rel/aop.ho/5.0/aop_proc/core/pmic/pm/drivers/clk/src/pm_clk.c#2 $
 
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
pm_err_flag_type pm_clk_sw_enable_status(uint8 pmic_chip, pm_clk_type periph, pm_on_off_type* on_off)
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
    else if (on_off == NULL)
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
                  clk_ptr->clk_reg_table->EN_CTL;

            err_flag = pm_comm_read_byte(clk_ptr->comm_ptr->slave_id, reg, &data, 0);

            if ((data & 0x80) == 0x80)
            {
                *on_off = PM_ON;
            }
            else
            {
                *on_off = PM_OFF;
            }
        }
    }

    return err_flag;
}

pm_err_flag_type pm_clk_ready_status(uint8 pmic_chip, pm_clk_type periph, boolean *clk_ready)
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
                  clk_ptr->clk_reg_table->STATUS1;

            err_flag = pm_comm_read_byte(clk_ptr->comm_ptr->slave_id, reg, &data, 0);

            if ((data & 0x80) == 0x80)
            {
                *clk_ready = TRUE;
            }
            else
            {
                *clk_ready = FALSE;
            }
        }
    }

    return err_flag;
}
