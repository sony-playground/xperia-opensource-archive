/*! \file pm_app_vrm.c
 *  \n
 *  \brief Implementation file for VRM resource related application level APIs. 
 *  \n  
 *  \n &copy; Copyright 2016 - 2017 QUALCOMM Technologies Incorporated, All Rights Reserved
 */

/* =======================================================================
                             Edit History
  This section contains comments describing changes made to this file.
  Notice that changes are listed in reverse chronological order.

$Header: //components/rel/aop.ho/5.0/aop_proc/core/pmic/pm/app/vrm/src/pm_app_vrm.c#6 $
 
when        who     what, where, why
--------    ---     ----------------------------------------------------------
11/23/16    kt       Created
28/09/22	bde		Updated PM_MIN_SETTLING_TIME_POLL_THR
========================================================================== */
/*===========================================================================

                     INCLUDE FILES 

===========================================================================*/
#include "pm_app_vrm_init.h"
#include "pm_debug.h"
#include "pm_rpmh_target.h"
#include "pm_app_pwr.h"
#include "pm_config_target.h"
#include "pm_resources_and_types.h"

//******************************************************************************
// Macros / Definitions / Constants
//******************************************************************************

/* The number of times we multiply the estimated settling time to
   calculate the maximum allowed settling time on a resource */
#define PM_MAX_SETTLING_TIME_MULTIPLIER   8

/* The minimum settling time resource needs to be given to settle
   while polling for vreg READY/OK status */
#define PM_MIN_SETTLING_TIME_POLL_THR     600 //uS

#define PM_SETTLING_TIME_POLL_INTERVAL    25 //uS

#define PM_STATUS1_REG_OFFSET 0x08
#define PM_VSET_VALID_LB_REG_OFFSET 0x40
#define PM_STATUS_OK_MASK 0x80

/* PBS seq related macros */

//Max PBS seq wait time in uS 
#define PM_PBS_SEQ_MAX_WAIT_TIME 800

//Busy Wait PBS seq done Poll time in uS 
#define PM_PBS_SEQ_BUSYWAIT_POLL_TIME 5

//PBS seq in execution busy indicator
#define PM_PBS_SEQ_BUSY_INDICATOR 0xFF

#define PBS_CLIENT_SLAVE_INDEX                   0x00
#define PBS_CLIENT_BASE_ADDR                     0x7200
#define PBS_CLIENT_PERIPH_OFFSET                 0x100
#define PBS_CLIENT_TRIG_CTL_OFFSET               0x42
#define PBS_CLIENT_ARGUMENT_OFFSET               0x50
#define PBS_CLIENT_RETURN_OFFSET                 0x51

#define PM_PON_RESET_N_CTL_ADDR                  0x899
#define PM_PON_RESET_N_MASK                      0x80
#define PM_PON_PS_HOLD_MASK                      0x80
#define PM_PON_PSHOLD_STATUS_ADDRESS             0x89A

//******************************************************************************
// Global Data
//******************************************************************************

pm_app_vrm_info_type pm_app_vrm_info = {0};

//******************************************************************************
// Local Helper Functions
//******************************************************************************
static void pm_app_vrm_lock()
{
    pm_lock(&pm_app_vrm_info.lock);
    pm_app_vrm_info.lock_count++;
}

static void pm_app_vrm_unlock()
{
  pm_app_vrm_info.lock_count--;
  CORE_VERIFY(pm_app_vrm_info.lock_count >= 0);
  pm_unlock(&pm_app_vrm_info.lock);
}

static pm_err_flag_type 
pm_app_vrm_settle_status_reg_dump(uint8 slave_id, uint16 base_address, pm_vreg_register_status* status)
{
    pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
    pm_register_address_type reg = 0x0;

    status->time_stamp = time_service_now();

    status->slave_id = slave_id;
    status->base_address = base_address;

    reg = (pm_register_address_type)(base_address + PM_STATUS1_REG_OFFSET);
    err_flag |= pm_comm_read_byte_array(slave_id, reg, PM_VREG_NUM_STATUS_REGS, status->status1_base_reg_dump, 0);

    reg = (pm_register_address_type)(base_address + PM_VSET_VALID_LB_REG_OFFSET);
    err_flag |= pm_comm_read_byte_array(slave_id, reg, PM_VREG_NUM_CFG_REGS, status->vset_lb_base_reg_dump, 0);

    reg = (pm_register_address_type)(base_address + PM_VREG_INT_RT_OFFS);
    err_flag |= pm_comm_read_byte_array(slave_id, reg, PM_VREG_NUM_INT_REGS, status ->int_base_reg_dump, 0);

    return err_flag;
}

static pm_err_flag_type 
pm_app_vrm_pbs_wait_seq_done(uint32 slave_id, uint16 ret_addr, uint8* ret_val)
{
    pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
    uint32 wait_time = 0;
    uint8 ret_data = 0;

    do
    {   //Read Scratch1 register
        err_flag |= pm_comm_read_byte(slave_id, ret_addr, &ret_data, 0);
        
        if(ret_data == PM_PBS_SEQ_BUSY_INDICATOR)
        {   
            //Wait for completion of PBS sequence in progress
            busywait(PM_PBS_SEQ_BUSYWAIT_POLL_TIME);
            if ((wait_time += PM_PBS_SEQ_BUSYWAIT_POLL_TIME) >= PM_PBS_SEQ_MAX_WAIT_TIME) 
            {   
                //Return error flag if sequence is not competed in max time
                err_flag = PM_ERR_FLAG_DATA_VERIFY_ERR;
                break; 
            }
        }
    }while (ret_data==PM_PBS_SEQ_BUSY_INDICATOR);

    if (ret_val != NULL)
    {
        *ret_val = ret_data;
    }
    
    return err_flag;
}

// get the PS_HOLD/RESET_N status
static pm_err_flag_type
pm_app_vrm_get_reset_sts(boolean* reset_sts)
{
    pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
    uint8 reset_sts_data[2];

    err_flag = pm_comm_read_byte_array(0, PM_PON_RESET_N_CTL_ADDR, 2, reset_sts_data, 0);

    if (((reset_sts_data[0] & PM_PON_RESET_N_MASK) == 0) ||
        ((reset_sts_data[1] & PM_PON_PS_HOLD_MASK) == 0))
    {
        *reset_sts = TRUE;
    }
    else
    {
        *reset_sts = FALSE;
    }
    
    return err_flag;
}


pm_err_flag_type 
pm_app_vrm_vreg_get_pwr_info(uint32 pmic_index, pm_vrm_periph_type periph_type, pm_app_vrm_pwr_info *pwr_info)
{
    pm_smps_data_type *smps_ptr = NULL;
    pm_ldo_data_type *ldo_ptr = NULL;
    pm_bob_data_type *bob_ptr = NULL;

    if (pwr_info == NULL)
    {
        return PM_ERR_FLAG_INVALID_PARAMETER;
    }

    switch (periph_type)
    {
       case PM_VRM_PERIPH_SMPS:
         smps_ptr = pm_smps_get_data(pmic_index);
         if (smps_ptr != NULL)
         {
             pwr_info->pwr_data = &smps_ptr->pm_pwr_data;
             pwr_info->comm_ptr = smps_ptr->comm_ptr;
         }
         pwr_info->rsrc_prop_id = PM_PROP_SMPS_RSRC;
         pwr_info->dep_prop_id = PM_PROP_SMPS_DEP;
         pwr_info->rail_prop_id = PM_PROP_SMPS_RAIL;
         break;

       case PM_VRM_PERIPH_LDO:
         ldo_ptr = pm_ldo_get_data(pmic_index);
         if (ldo_ptr != NULL)
         {
             pwr_info->pwr_data = &ldo_ptr->pm_pwr_data;
             pwr_info->comm_ptr = ldo_ptr->comm_ptr;
         }
         pwr_info->rsrc_prop_id = PM_PROP_LDO_RSRC;
         pwr_info->dep_prop_id = PM_PROP_LDO_DEP;
         pwr_info->rail_prop_id = PM_PROP_LDO_RAIL;
         break;

       case PM_VRM_PERIPH_BOB:
         bob_ptr = pm_bob_get_data(pmic_index);
         if (bob_ptr != NULL)
         {
             pwr_info->pwr_data = &bob_ptr->pm_pwr_data;
             pwr_info->comm_ptr = bob_ptr->comm_ptr; 
         }
         pwr_info->rsrc_prop_id = PM_PROP_BOB_RSRC;
         pwr_info->dep_prop_id = PM_PROP_BOB_DEP;
         pwr_info->rail_prop_id = PM_PROP_BOB_RAIL;
         break;

       default:
        return PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
    }
    
    return PM_ERR_FLAG_SUCCESS;
}

/*===========================================================================

                     API IMPLEMENTATION 

===========================================================================*/
pm_err_flag_type 
pm_app_vrm_vreg_settle_status(pm_vrm_periph_info *periph_info, uint32 estimated_time_us, boolean *vreg_status, uint8 *pshold_status)
{

    pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
    pm_app_vrm_pwr_info pwr_info = {0};
    boolean settle_status = FALSE;
    uint64 settle_start_time = 0;
    uint64 settle_end_time = 0;
    uint64 current_time = 0;
    uint32 max_time_us = 0;
    uint32 slave_id = 0;
    uint16 base_addr = 0;
	uint8 pshold_status_val = 0;
    boolean reset_status = FALSE;
	uint8 read_voltage_data[2] = {0, 0};
    uint8 status = 0;

    if ((periph_info == NULL) || (vreg_status == NULL))
    {  
        return PM_ERR_FLAG_INVALID_PARAMETER;
    }

    if (pm_app_vrm_info.initialized == FALSE)
    {
        return PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
    }

    pm_app_vrm_lock();

    err_flag = pm_app_vrm_vreg_get_pwr_info(periph_info->pmic_index, periph_info->periph_type, &pwr_info);

   if ((pwr_info.pwr_data == NULL) || (pwr_info.comm_ptr == NULL))
   {
    return PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
   }

	
    slave_id = pwr_info.comm_ptr->slave_id;
    base_addr = pwr_info.pwr_data->pwr_specific_info[periph_info->periph_index].periph_base_address;
    err_flag = pm_comm_read_byte(slave_id, (base_addr+0x8), &status, 0);

    if ((status & 0x4) && (!(status & 0x80)))
	{
	    err_flag |= pm_comm_read_byte_array(slave_id, (base_addr + 0x40), 2, read_voltage_data, 0);
		read_voltage_data[0] += 4; //increase voltage by 4mV 
		err_flag |= pm_comm_write_byte_array(slave_id, (base_addr + 0x40), 2, read_voltage_data, 0);
		read_voltage_data[0] -= 4; //revert to original voltage
		err_flag |= pm_comm_write_byte_array(slave_id, (base_addr + 0x40), 2, read_voltage_data, 0);
	}


    if ((err_flag != PM_ERR_FLAG_SUCCESS))
    {  
        return PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
    }

    max_time_us = PM_MAX_SETTLING_TIME_MULTIPLIER * estimated_time_us;

    if(max_time_us < PM_MIN_SETTLING_TIME_POLL_THR)
    {
        max_time_us = PM_MIN_SETTLING_TIME_POLL_THR;
    }

    //enable the pmos ldo force soft start bit
    if(periph_info->periph_type == PM_VRM_PERIPH_LDO)
    {
        err_flag = pm_pwr_pmos_soft_start_en_alg(pwr_info.pwr_data, pwr_info.comm_ptr, periph_info->periph_index, PM_ON);
        
        if(err_flag == PM_ERR_FLAG_SUCCESS)
        {
            pm_app_vrm_info.force_soft_start_count = pm_app_vrm_info.force_soft_start_count + 1 ;
        }
        if(err_flag == PM_ERR_FLAG_FEATURE_NOT_SUPPORTED)
        {
            err_flag = PM_ERR_FLAG_SUCCESS;
        }        
    }
    /* Get the settle start time */
    settle_start_time = time_service_now();

    settle_end_time = settle_start_time + pm_convert_time_to_timetick(max_time_us);

    current_time = settle_start_time;

    do
    {
    pm_pwr_is_vreg_ready_alg(pwr_info.pwr_data, pwr_info.comm_ptr, periph_info->periph_index, &settle_status);
    
        busywait(PM_SETTLING_TIME_POLL_INTERVAL);
        /* Get the current time and check if the maximum allowed settle time on the vreg has elapsed */
        current_time = time_service_now();

    } while( (settle_status == FALSE) && (current_time < settle_end_time) );

    settle_end_time = current_time; // calculating the actual end time 

    slave_id = pwr_info.comm_ptr->slave_id;
    base_addr = pwr_info.pwr_data->pwr_specific_info[periph_info->periph_index].periph_base_address;


    if(pm_app_vrm_info.vreg_settle_arr_index >= PM_VREG_SETTLE_ARR_SIZE)
    {
        /* reset the settle array index */
        pm_app_vrm_info.vreg_settle_arr_index = 0;
    }

    /* saving the settling info for the error case */
    pm_app_vrm_info.vreg_settle_arr[pm_app_vrm_info.vreg_settle_arr_index].settle_start_time = settle_start_time;
    pm_app_vrm_info.vreg_settle_arr[pm_app_vrm_info.vreg_settle_arr_index].settle_end_time = settle_end_time;

    pm_app_vrm_settle_status_reg_dump(slave_id, base_addr, &pm_app_vrm_info.vreg_settle_arr[pm_app_vrm_info.vreg_settle_arr_index].status);

    pm_app_vrm_get_reset_sts(&reset_status);
    if(!reset_status)
    {
        pshold_status_val = 0x80;
    }

    pm_app_vrm_info.vreg_settle_arr[pm_app_vrm_info.vreg_settle_arr_index].pshold_status = pshold_status_val;

    pm_app_vrm_info.vreg_settle_arr_index = pm_app_vrm_info.vreg_settle_arr_index + 1;

    if(settle_status == TRUE)
    {
        //disable the pmos ldo force soft start bit
        if(periph_info->periph_type == PM_VRM_PERIPH_LDO)
        {
            pm_pwr_pmos_soft_start_en_alg(pwr_info.pwr_data, pwr_info.comm_ptr, periph_info->periph_index, PM_OFF);            
        }
    }

    *vreg_status = settle_status;
    *pshold_status = pshold_status_val;

    pm_app_vrm_unlock();
    
    return err_flag;
}


pm_err_flag_type 
pm_app_vrm_vreg_ocp_status_clear(pm_vrm_periph_info *periph_info, boolean *ocp_status)
{

    pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
    pm_app_vrm_pwr_info pwr_info = {0};

    if ((periph_info == NULL) || (ocp_status == NULL))
    {  
        return PM_ERR_FLAG_INVALID_PARAMETER;
    }

    if (pm_app_vrm_info.initialized == FALSE)
    {
        return PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
    }

    pm_app_vrm_lock();

    err_flag = pm_app_vrm_vreg_get_pwr_info(periph_info->pmic_index, periph_info->periph_type, &pwr_info);

    if ((err_flag != PM_ERR_FLAG_SUCCESS) || (pwr_info.pwr_data == NULL) || (pwr_info.comm_ptr == NULL))
    {  
        return PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
    }

    err_flag = pm_pwr_ocp_latched_status_clear_alg(pwr_info.pwr_data, pwr_info.comm_ptr, periph_info->periph_index, ocp_status);

    if (*ocp_status == TRUE)
    {
        if (pm_app_vrm_info.vreg_ocp_arr_index >= PM_VREG_OCP_ARR_SIZE)
        {
            pm_app_vrm_info.vreg_ocp_arr_index = 0;
        }
        pm_app_vrm_info.vreg_ocp_arr[pm_app_vrm_info.vreg_ocp_arr_index].time_stamp = time_service_now();
        pm_app_vrm_info.vreg_ocp_arr[pm_app_vrm_info.vreg_ocp_arr_index].pmic_index = periph_info->pmic_index;
        pm_app_vrm_info.vreg_ocp_arr[pm_app_vrm_info.vreg_ocp_arr_index].periph_type = periph_info->periph_type;
        pm_app_vrm_info.vreg_ocp_arr[pm_app_vrm_info.vreg_ocp_arr_index].periph_id = periph_info->periph_index + 1;
        pm_app_vrm_info.vreg_ocp_arr_index = pm_app_vrm_info.vreg_ocp_arr_index + 1; 
        pm_app_vrm_info.vreg_ocp_count = pm_app_vrm_info.vreg_ocp_count + 1;
    }

    pm_app_vrm_unlock();
    
    return err_flag;
}

/*pm_err_flag_type 
pm_app_vrm_pbs_sw_trigger(pm_vrm_periph_info *periph_info, uint8 trig_arg, pm_vrm_pbs_seq_status *seq_status)
{
    pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
    uint32 pmic_min_id = 1;
    uint32 pmic_id = 1;
    uint32 pmic_index = 0;
    uint32 pbs_slave_id = 0;
    uint16 pbs_addr = 0;
    uint16 trig_addr = 0;
    uint16 arg_addr = 0;
    uint16 ret_addr = 0;

    if ((periph_info == NULL) || (seq_status == NULL))
    {  
        return PM_ERR_FLAG_INVALID_PARAMETER;
    }

    if ((pm_app_vrm_info.initialized == FALSE) || (periph_info->periph_type != PM_VRM_PERIPH_PBS_CLIENT))
    {
        return PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
    }

    pm_app_vrm_lock();

    pmic_id = periph_info->pmic_index + 1;
    pmic_min_id = periph_info->pmic_index + 1;

    if (pmic_id >= PM_MAX_NUM_PMICS)
    {
        pmic_id = PM_MAX_NUM_PMICS;
        pmic_min_id = 1;
    }

    pbs_addr = PBS_CLIENT_BASE_ADDR + ((periph_info->periph_index) * PBS_CLIENT_PERIPH_OFFSET);
    trig_addr = pbs_addr + PBS_CLIENT_TRIG_CTL_OFFSET;
    arg_addr = pbs_addr + PBS_CLIENT_ARGUMENT_OFFSET;
    ret_addr = pbs_addr + PBS_CLIENT_RETURN_OFFSET;

    if (pm_get_slave_id(periph_info->pmic_index, PBS_CLIENT_SLAVE_INDEX, &pbs_slave_id) == PM_ERR_FLAG_SUCCESS)
    {
        err_flag |= pm_comm_write_byte(pbs_slave_id, ret_addr, PM_PBS_SEQ_BUSY_INDICATOR, 0);
        err_flag |= pm_comm_write_byte(pbs_slave_id, arg_addr, trig_arg, 0);
        err_flag |= pm_comm_write_byte(pbs_slave_id, trig_addr, 0x80, 0);

        // get the PS_HOLD/RESET_N status
        pm_app_vrm_get_reset_sts(&(seq_status->reset_sts));
    }

    while ((pmic_id >= pmic_min_id) && (err_flag == PM_ERR_FLAG_SUCCESS))
    {
        pmic_index = pmic_id - 1;

        if (pm_get_slave_id(pmic_index, PBS_CLIENT_SLAVE_INDEX, &pbs_slave_id) == PM_ERR_FLAG_SUCCESS)
        {
            seq_status->pmic_index = pmic_index;

            // wait for PBS sequence done
            err_flag |= pm_app_vrm_pbs_wait_seq_done(pbs_slave_id, ret_addr, &(seq_status->ret_val));
        }

        pmic_id = pmic_id - 1;
    }

    pm_app_vrm_unlock();
    
    return err_flag;
}*/

pm_err_flag_type pm_app_rpmh_core_rail_set_voltage( pm_core_rail_name rail ,uint64 voltage_uV, pm_request_type active_ret)
{
    pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;

    if ( INVALID == active_ret || INVALID_NAME==rail )
    {
        return PM_ERR_FLAG_SUCCESS;
    }

    err_flag = pm_rpmh_target_core_rail_set_voltage(rail ,voltage_uV, active_ret);

    CORE_VERIFY(err_flag==PM_ERR_FLAG_SUCCESS);

    return err_flag;
}

pm_err_flag_type 
pm_app_vrm_clk_settle_log(pm_vrm_periph_info *periph_info, uint32 estimated_time_us, boolean *clk_status, uint8 *pshold_status)
{
    pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
    boolean reset_status = FALSE;
    uint8 pshold_status_val = 0;
    boolean clk_ready_status = FALSE;
    boolean en_status = FALSE;

    if (periph_info == NULL)
    {  
        return PM_ERR_FLAG_INVALID_PARAMETER;
    }

    pm_clk_data_type *clk_ptr = pm_clk_get_data(periph_info->pmic_index);

     if (clk_ptr == NULL)
    {  
        return PM_ERR_FLAG_INVALID_PARAMETER;
    }   

    if (pm_app_vrm_info.initialized == FALSE)
    {
        return PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
    }

    pm_app_vrm_lock();

    pm_app_vrm_info.clk_settle_status_info.time_stamp = time_service_now();
    pm_app_vrm_info.clk_settle_status_info.slave_id = clk_ptr->comm_ptr->slave_id;
    pm_app_vrm_info.clk_settle_status_info.base_address = clk_ptr->base_address;

    pm_app_vrm_get_reset_sts(&reset_status);
    if(!reset_status)
    {
        pshold_status_val = PM_STATUS_OK_MASK;
    }
    pm_app_vrm_info.clk_settle_status_info.pshold_status = pshold_status_val;
    *pshold_status = pshold_status_val;

    pm_clk_sw_enable_status(periph_info->pmic_index, clk_ptr->clk_common[periph_info->periph_index], &en_status);
    pm_app_vrm_info.clk_settle_status_info.enable_status = en_status;

    pm_clk_ready_status(periph_info->pmic_index, clk_ptr->clk_common[periph_info->periph_index], &clk_ready_status);
    pm_app_vrm_info.clk_settle_status_info.clk_status = clk_ready_status;
    *clk_status = clk_ready_status;

    pm_app_vrm_unlock();
    
    return err_flag;
}
