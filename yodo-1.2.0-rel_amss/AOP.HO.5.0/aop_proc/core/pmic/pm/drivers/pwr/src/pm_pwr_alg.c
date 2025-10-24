/*! \file pm_pwr_alg.c 
*  \n
*  \brief  
*  \n  
*  \n &copy; Copyright 2012-2018 QUALCOMM Technologies Incorporated, All Rights Reserved
*/

/* =======================================================================
                             Edit History
  This section contains comments describing changes made to this file.
  Notice that changes are listed in reverse chronological order.

$Header: //components/rel/aop.ho/5.0/aop_proc/core/pmic/pm/drivers/pwr/src/pm_pwr_alg.c#1 $

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

#define VREG_READY_MASK   0x80
#define STEPPER_DONE_MASK 0x04
#define PWR_MODE_MASK     0x7


// SMPS VREG_ACK delay issue Work-around enablement status (PMICPR-2654)
// PMICPR-2654: Unexpected delay in VREG_ACK INT after VSET step up while lightly loaded and discharging after step down
// This work-around will handle high cap discharge settling time work-arounds as well so applying this for LDOs as well
static boolean 
pm_pwr_vreg_ack_dly_wa_flag(pm_pwr_data_type *pwr_data, pm_comm_info_type *comm_ptr, uint32 peripheral_index)
{
   boolean vreg_ack_dly_wa = FALSE;
   pm_model_type pmic_model = PMIC_IS_UNKNOWN;
   uint8 pmic_major_rev = 0;

   // SMPS VREG_ACK delay issue work-around of using STEPPER_DONE instead of VREG_READY needs to be used for following PMICs
   // PM855 v1.0/v2.0
   // PM855A/L/P v1.0/v2.0
   // PM8009 v1.0
   // PMX24 v1.0
   // This work-around will handle high cap discharge settling time work-arounds as well so applying this for LDOs as well
   if (pwr_data->pwr_specific_info[peripheral_index].is_periph_stepper)
   {
      pmic_model = pm_get_pmic_model(comm_ptr->pmic_index);
      pmic_major_rev = pm_get_pmic_revision(comm_ptr->pmic_index);

      if ((pmic_model == PMIC_IS_PM855) || (pmic_model == PMIC_IS_PM855L))
      {
          if (pmic_major_rev < 3)
          {
             vreg_ack_dly_wa = TRUE;
          }
      }
      else if ((pmic_model == PMIC_IS_PMX24) || (pmic_model == PMIC_IS_PM8009) || 
               (pmic_model == PMIC_IS_PM855A) || (pmic_model == PMIC_IS_PM855P))
      {
          if (pmic_major_rev < 2)
          {
             vreg_ack_dly_wa = TRUE;
          }
      }
   }

   return vreg_ack_dly_wa;
}
/*===========================================================================

                     FUNCTION IMPLEMENTATION 

===========================================================================*/
pm_err_flag_type pm_pwr_sw_mode_raw_alg(pm_pwr_data_type *pwr_data, pm_comm_info_type *comm_ptr, uint32 peripheral_index, uint8 mode)
{
    pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;

    if ((peripheral_index >= pwr_data->num_of_peripherals) || (pwr_data->pwr_specific_info[peripheral_index].periph_type == 0))
    {
        err_flag = PM_ERR_FLAG_PERIPHERAL_ERR;
    }
    else if (mode > PWR_MODE_MASK)
    {
        err_flag = PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
    }
    else if (pwr_data->pwr_specific_info[peripheral_index].is_periph_unified_reg == FALSE)
    {
        err_flag = PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
    }
    else
    {
        pm_register_address_type reg = 0x0;
        pm_register_data_type data = mode;
            
        reg = (pm_register_address_type)(pwr_data->pwr_specific_info[peripheral_index].periph_base_address + pwr_data->pwr_reg_table->MODE_CTL);

        err_flag = pm_comm_write_byte(comm_ptr->slave_id, reg, data, 0);
    }

    return err_flag;
}

pm_err_flag_type pm_pwr_sw_mode_status_raw_alg(pm_pwr_data_type *pwr_data, pm_comm_info_type *comm_ptr, uint32 peripheral_index, uint8 *mode_ctl)
{
    pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
                                                          
    if ((peripheral_index >= pwr_data->num_of_peripherals) || (pwr_data->pwr_specific_info[peripheral_index].periph_type == 0))
    {
        err_flag = PM_ERR_FLAG_PERIPHERAL_ERR;
    }
    else if (mode_ctl == NULL)
    {
        err_flag = PM_ERR_FLAG_INVALID_PARAMETER;
    }
    else
    {
        pm_register_address_type           reg = 0x0;
        pm_register_data_type              data = 0xFF;
            
        reg = (pm_register_address_type)(pwr_data->pwr_specific_info[peripheral_index].periph_base_address + pwr_data->pwr_reg_table->MODE_CTL);

        err_flag = pm_comm_read_byte(comm_ptr->slave_id, reg, &data, 0);
        
        if (err_flag == PM_ERR_FLAG_SUCCESS)
        {
            *mode_ctl = data;
        }
    }

    return err_flag;
}

pm_err_flag_type pm_pwr_sw_enable_alg(pm_pwr_data_type *pwr_data, pm_comm_info_type *comm_ptr, uint32 peripheral_index, pm_on_off_type on_off)
{
    pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;

    if ((peripheral_index >= pwr_data->num_of_peripherals) || (pwr_data->pwr_specific_info[peripheral_index].periph_type == 0))
    {
        err_flag = PM_ERR_FLAG_PERIPHERAL_ERR;
    }
    else if (on_off >= PM_INVALID)
    {
        err_flag = PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
    }
    else
    {
        pm_register_address_type reg = 0x0;
        pm_register_data_type data = 0;
            
        reg = (pm_register_address_type)(pwr_data->pwr_specific_info[peripheral_index].periph_base_address + pwr_data->pwr_reg_table->EN_CTL);

        if (PM_OFF == on_off)
        {
            data = 0;
        }
        else
        {
            data = 0x80;
        }

        if (pwr_data->pwr_specific_info[peripheral_index].is_periph_unified_reg ==  TRUE)
        {
            err_flag = pm_comm_write_byte(comm_ptr->slave_id, reg, data, 0);
        }
        else
        {
            err_flag = pm_comm_write_byte_mask(comm_ptr->slave_id, reg, 0x80, data, 0);
        }
    }

    return err_flag;
}

pm_err_flag_type pm_pwr_sw_enable_status_alg(pm_pwr_data_type *pwr_data, pm_comm_info_type *comm_ptr, uint32 peripheral_index, pm_on_off_type *on_off)
{
    pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;

    if ((peripheral_index >= pwr_data->num_of_peripherals) || (pwr_data->pwr_specific_info[peripheral_index].periph_type == 0))
    {
        err_flag = PM_ERR_FLAG_PERIPHERAL_ERR;
    }
    else if (on_off == NULL)
    {
        err_flag = PM_ERR_FLAG_INVALID_PARAMETER;
    }
    else
    {
        pm_register_address_type           reg = 0x0;
        pm_register_data_type              data = 0;

        reg = (pm_register_address_type)(pwr_data->pwr_specific_info[peripheral_index].periph_base_address + pwr_data->pwr_reg_table->EN_CTL);

        err_flag = pm_comm_read_byte(comm_ptr->slave_id, reg, &data, 0);
        if (err_flag != PM_ERR_FLAG_SUCCESS)
        {
            *on_off = PM_INVALID;
            return err_flag;
        }

        if (data & 0x80)
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

pm_err_flag_type pm_pwr_is_vreg_ready_alg(pm_pwr_data_type *pwr_data, pm_comm_info_type *comm_ptr, uint32 peripheral_index, boolean *vreg_ready)
{
    pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
    uint8 vreg_mask = 0;
    uint8 periph_type = 0;

    if (peripheral_index >= pwr_data->num_of_peripherals || 
             pwr_data->pwr_specific_info[peripheral_index].periph_type == 0)
    {
        err_flag = PM_ERR_FLAG_PERIPHERAL_ERR;
    }
    else if (vreg_ready == NULL)
    {
        err_flag = PM_ERR_FLAG_INVALID_PARAMETER;
    }
    else
    {
        pm_register_address_type reg = 0x0;
        pm_register_data_type data = 0;
        periph_type = pwr_data->pwr_specific_info[peripheral_index].periph_type;

        reg = (pm_register_address_type)(pwr_data->pwr_specific_info[peripheral_index].periph_base_address + pwr_data->pwr_reg_table->STATUS);

        err_flag = pm_comm_read_byte(comm_ptr->slave_id, reg, &data, 0);
        if (err_flag != PM_ERR_FLAG_SUCCESS)
        {
            err_flag = pm_comm_read_byte(comm_ptr->slave_id, reg, &data, 0);
            if (err_flag != PM_ERR_FLAG_SUCCESS)
            {
                *vreg_ready = FALSE;
                return err_flag;
            }
        }

        // SMPS VREG_ACK delay issue work-around of using STEPPER_DONE instead of VREG_READY
        // this work-around will help with high cap discharge settling time issue as well
        if (pm_pwr_vreg_ack_dly_wa_flag(pwr_data, comm_ptr, peripheral_index))
        {
            vreg_mask = STEPPER_DONE_MASK;
        }
        else
        {
            vreg_mask = VREG_READY_MASK;
        }

        if ((data & vreg_mask) == vreg_mask)
        {
            *vreg_ready = TRUE;
        }
        else
        {
            *vreg_ready = FALSE;
        }
    }

    return err_flag;
}

pm_err_flag_type pm_pwr_volt_level_alg(pm_pwr_data_type *pwr_data, pm_comm_info_type *comm_ptr, uint32 peripheral_index, pm_volt_level_type  volt_level)
{
    pm_err_flag_type                  err_flag = PM_ERR_FLAG_SUCCESS;
    uint32                            vmin = 0;  // microvolt
    uint32                            vStep = 0; // microvolt
    uint32                            calculated_vset = 0;
    pm_register_data_type             vset_ht[2] = {0};
    pm_register_address_type          reg = 0;

    if (peripheral_index >= (pwr_data->num_of_peripherals) || 
            pwr_data->pwr_specific_info[peripheral_index].periph_type == 0)
    {
        err_flag = PM_ERR_FLAG_PERIPHERAL_ERR ;
    }
    else if (pwr_data->pwr_specific_info[peripheral_index].is_periph_unified_reg == FALSE)
    {
        err_flag = PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
    }
    else
    {
        if ((volt_level <= pwr_data->pwr_specific_info[peripheral_index].pwr_vset.RangeMax) && 
            (volt_level >= pwr_data->pwr_specific_info[peripheral_index].pwr_vset.RangeMin) )
        {
            vmin = pwr_data->pwr_specific_info[peripheral_index].pwr_vset.RangeMin;
            vStep = pwr_data->pwr_specific_info[peripheral_index].pwr_vset.VStep;
        }
       
        if (vStep > 0)
        {
            calculated_vset = (volt_level - vmin)/vStep;

            vset_ht[0] = ((calculated_vset) & 0xFF);
            vset_ht[1] = ((calculated_vset>>8) & 0xFF);

            reg =  (pm_register_address_type)(pwr_data->pwr_specific_info[peripheral_index].periph_base_address + pwr_data->pwr_reg_table->VOLTAGE_CTRL1);

            // Set vset
            err_flag = pm_comm_write_byte_array(comm_ptr->slave_id, reg, 2, vset_ht, 0);
        }
        else
        {
            err_flag = PM_ERR_FLAG_DATA_VERIFY_ERR;
        }
    }

    return err_flag;
}

pm_err_flag_type pm_pwr_volt_level_status_alg(pm_pwr_data_type *pwr_data, pm_comm_info_type *comm_ptr, uint32 peripheral_index, pm_volt_level_type *volt_level)
{
    pm_err_flag_type                 err_flag = PM_ERR_FLAG_SUCCESS;
    uint32                           vmin = 0; // microvolt
    uint32                           vStep = 0; //microvolt
    uint16                           vset_ht = 0;
    pm_register_address_type         reg = 0;
    pm_register_data_type            reg_data[2] = {0};

    if (peripheral_index >= (pwr_data->num_of_peripherals) || 
            pwr_data->pwr_specific_info[peripheral_index].periph_type == 0)
    {
        err_flag = PM_ERR_FLAG_PERIPHERAL_ERR;
    }
    else if (volt_level == NULL)
    {
        err_flag = PM_ERR_FLAG_INVALID_PARAMETER;
    }
    else if (pwr_data->pwr_specific_info[peripheral_index].is_periph_unified_reg == FALSE)
    {
        err_flag = PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
    }
    else
    {

        // get the voltage level LUT
        reg =  (pm_register_address_type)(pwr_data->pwr_specific_info[peripheral_index].periph_base_address + pwr_data->pwr_reg_table->VOLTAGE_CTRL1);

        err_flag |= pm_comm_read_byte_array(comm_ptr->slave_id, reg, 2, reg_data, 0);

        if ( err_flag == PM_ERR_FLAG_SUCCESS )
        {
            vmin = pwr_data->pwr_specific_info[peripheral_index].pwr_vset.RangeMin; // microvolt
            vStep = pwr_data->pwr_specific_info[peripheral_index].pwr_vset.VStep; //microvolt

            vset_ht = (reg_data[1]<<8) | (reg_data[0]);
            *volt_level = vmin + vset_ht * vStep;
        }
    }

    return err_flag;
}

pm_err_flag_type pm_pwr_ocp_latched_status_clear_alg(pm_pwr_data_type *pwr_data, pm_comm_info_type *comm_ptr, uint8 peripheral_index, boolean *ocp_occured)
{
    pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
    pm_register_address_type ocp_status_reg = 0x0;
    pm_register_address_type ocp_reg = 0x0;
    pm_register_address_type sec_reg = 0x0;
    pm_register_data_type status_data = 0;
    pm_register_data_type ocp_clear_data = 0;
    pm_register_data_type status_mask = 0;
    pm_register_data_type ocp_clear_mask = 0;

    if ((peripheral_index >= pwr_data->num_of_peripherals) || (pwr_data->pwr_specific_info[peripheral_index].periph_type == 0))
    {
        err_flag = PM_ERR_FLAG_PERIPHERAL_ERR;
    }
    else if(NULL == ocp_occured)
    {
        err_flag = PM_ERR_FLAG_INVALID_PARAMETER;
    }
    else
    {
        if (pwr_data->pwr_specific_info[peripheral_index].is_periph_unified_reg == TRUE)
        {
            ocp_status_reg = (pm_register_address_type)(pwr_data->pwr_specific_info[peripheral_index].periph_base_address + pwr_data->pwr_reg_table->STATUS);
            status_mask = 0x1 << 5;
            
            if (pwr_data->pwr_specific_info[peripheral_index].pmic4_flag == TRUE)
            {
                ocp_reg = (pm_register_address_type)(pwr_data->pwr_specific_info[peripheral_index].periph_base_address + pwr_data->pwr_reg_table->PMIC4_OCP);
            }
            else
            {
                ocp_reg = (pm_register_address_type)(pwr_data->pwr_specific_info[peripheral_index].periph_base_address + pwr_data->pwr_reg_table->OCP);
            }
            
            ocp_clear_mask = 0x1 << 1;
            ocp_clear_data = 0x1 << 1;
        }
        else
        {
            return PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
        }

        err_flag = pm_comm_read_byte(comm_ptr->slave_id, ocp_status_reg, &status_data, 0);

        if (err_flag != PM_ERR_FLAG_SUCCESS)
        {
            err_flag = pm_comm_read_byte(comm_ptr->slave_id, ocp_status_reg, &status_data, 0);
        }

        *ocp_occured = (status_data & status_mask) ? TRUE : FALSE ;

        if (*ocp_occured == TRUE)
        {
            sec_reg = (pm_register_address_type)(pwr_data->pwr_specific_info[peripheral_index].periph_base_address + pwr_data->pwr_reg_table->SEC_ACCESS);
            /*write 1 and then 0 to clear OCP*/
            err_flag |= pm_comm_write_byte(comm_ptr->slave_id, sec_reg, 0xA5, 0);
            err_flag |= pm_comm_write_byte_mask(comm_ptr->slave_id, ocp_reg, ocp_clear_mask, ocp_clear_data, 0);
            err_flag |= pm_comm_write_byte(comm_ptr->slave_id, sec_reg, 0xA5, 0);
            err_flag |= pm_comm_write_byte_mask(comm_ptr->slave_id, ocp_reg, ocp_clear_mask, 0, 0);
        }
    }

    return err_flag;
}

pm_err_flag_type pm_pwr_pmos_soft_start_en_alg(pm_pwr_data_type *pwr_data, pm_comm_info_type *comm_ptr, uint32 peripheral_index, pm_on_off_type on_off)
{
    pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
    pm_register_data_type soft_start_mask = 0x01;

    if ((peripheral_index >= pwr_data->num_of_peripherals) || (on_off >= PM_INVALID))
    {
        err_flag = PM_ERR_FLAG_INVALID_PARAMETER;
    }
    else
    {   
        if(pwr_data->pwr_specific_info[peripheral_index].is_soft_start_present)
        {
            pm_register_address_type reg = 0x0;
            pm_register_data_type data = 0;
        
            reg = (pm_register_address_type)(pwr_data->pwr_specific_info[peripheral_index].periph_base_address + pwr_data->pwr_reg_table->PMOS_FORCE_SOFT_START);

            if (PM_OFF == on_off)
            {
                data = 0;
            }
            else
            {
                data = 0x01;
            }

            err_flag = pm_comm_write_byte_mask(comm_ptr->slave_id, reg, soft_start_mask, data, 0);
        }
        else
        {
            err_flag = PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
        }       
    }

    return err_flag;
}
