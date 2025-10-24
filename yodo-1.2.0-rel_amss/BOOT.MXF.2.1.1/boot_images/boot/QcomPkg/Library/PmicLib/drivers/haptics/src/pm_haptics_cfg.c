
/*! \file haptics_api.c
*  \n
*  \details This file contains the top-level API wrappers for the Vib
*           peripheral.
*
*  \n &copy; Copyright 2012-2022 QUALCOMM Technologies Incorporated, All Rights Reserved
*/

/* =======================================================================
 
$Header: //components/rel/core.boot/6.1.1/QcomPkg/Library/PmicLib/drivers/haptics/src/pm_haptics_cfg.c#2 $
$Author: pwbldsvc $
$DateTime: 2022/11/01 23:32:28 $
when       who     what, where, why
--------   ---     ----------------------------------------------------------
02/14/19   pxm      Disable auto res for ERM mode and enable for LRA mode
05/03/17   czq      Supported for WF source selection.
03/20/17   czq      1. Added get haptics ststus1 API
                    2. Added get play rate configuration and LRA auto resonance API.
                    3. Adjusting rate configuration before haptics disable
08/07/15   al       Fixing mask and shift as per doc          
========================================================================== */

/*===========================================================================

                     INCLUDE FILES 

===========================================================================*/
#include "pm_haptics_cfg_driver.h"
#include "pm_version.h"

#include <api/pmic/pm/pm_sdam.h>
#include "pm_dt_parser.h"
#include "pm_dt.h"

#include "pm_chg.h"

/*===========================================================================

                GLOBAL TYPE DEFINITIONS

===========================================================================*/
static uint8 pm_haptics_vmax_hdrm = 0xA;     // Set 500mV headroom as default

#define PM_HAPTICS_VMAX_VOLT_HIGH            12750
#define PM_HAPTICS_VMAX_VOLT_LOW             0
#define PM_HAPTICS_VMAX_VOLT_FACTOR          50
#define PM_HAPTICS_ACTUATOR_TYPE_MASK        0x1
#define PM_HAPTICS_PLAY_MASK                 0x80
#define PM_HAPTICS_AUTO_RES_CFG_MASK         0x7F

#define SDAM_MEM_006  6

#define HAPTICS_REG_ADDR(x)                  haptics_ptr->base_address + haptics_ptr->haptics_reg_table->x

pm_err_flag_type pm_haptics_cfg_play(uint32 pmic_chip,  pm_on_off_type enable) 
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  pm_haptics_data_type *haptics_ptr = pm_haptics_get_data(pmic_chip);
  uint32 slave_id = 0;
  uint32 vmax_volt_mv = 1400;
  uint32 vbatt_min_mv = 0;
  uint32 vbatt_mv = 0;
  uint8 tlra_ol_h = 0x4;         /* TLRA Open loop, FLRA = 175Hz (default) */
  uint8 tlra_ol_l = 0x77;
  pm_dt_haptics_config  *haptics_dt = NULL;

  if (haptics_ptr == NULL) {
    return PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
  }

  slave_id = haptics_ptr->comm_ptr->slave_id;

  haptics_dt = pm_dt_get_node(PMIC_DT_NODE_PM_HAPTICS);
  if (haptics_dt) {
    pm_haptics_vmax_hdrm = haptics_dt->vmax_hdrm;
    vmax_volt_mv = haptics_dt->vmax_mv;
    tlra_ol_h = (haptics_dt->tlra_ol >> 8) & 0xff;
    tlra_ol_l = haptics_dt->tlra_ol & 0xff;
    vbatt_min_mv = haptics_dt->vbatt_min_mv;
  }

  if (enable == PM_ON) {
    /* Check for minimum battery voltage */
    err_flag = pm_chg_get_vbatt(&vbatt_mv);
    if (err_flag == PM_ERR_FLAG_SUCCESS) {
       if (vbatt_mv < vbatt_min_mv) {
          return err_flag;
       }
    }

    /* Start haptics vibration */
    err_flag = pm_comm_write_byte(slave_id, HAPTICS_REG_ADDR(spmi_play), 0x01);
    /* Enable auto resonance, set auto resonance delay to 6 cycles, and set error window to 25% */
    err_flag |= pm_comm_write_byte(slave_id, HAPTICS_REG_ADDR(autores_cfg), ((1<<7) | (12<<2) | (1 << 0)));      
    err_flag |= pm_haptics_set_vmax_volt(pmic_chip, vmax_volt_mv);

    err_flag |= pm_comm_write_byte(slave_id, HAPTICS_REG_ADDR(direct_play), 0xff);
    
    err_flag |= pm_comm_write_byte(slave_id, HAPTICS_REG_ADDR(tlra_ol_high), tlra_ol_h);
    err_flag |= pm_comm_write_byte(slave_id, HAPTICS_REG_ADDR(tlra_ol_low), tlra_ol_l);

    err_flag |= pm_comm_write_byte(slave_id, HAPTICS_REG_ADDR(fault_clr), 0x07);

    err_flag |= pm_comm_write_byte(slave_id, HAPTICS_REG_ADDR(spmi_play), 0x81);
  } else {
    uint8 status_buf[2];
    /* Save the calibration data into SDAM, only do this for PUHI 2.0 */
    pm_model_type pmic_model = pm_get_pmic_model(PMIC_D);
    uint8 pmic_rev = pm_get_pmic_revision(PMIC_D);
    if (pmic_model == PMIC_IS_PM8350B && pmic_rev >= 2) 
    {
       err_flag |= pm_comm_write_byte(slave_id, HAPTICS_REG_ADDR(mod_status_xt), 0x00);
       err_flag |= pm_comm_write_byte(slave_id, HAPTICS_REG_ADDR(mod_status_sel), 0x00);
       err_flag |= pm_comm_read_byte(slave_id, HAPTICS_REG_ADDR(status_data_msb), &status_buf[0]);
       err_flag |= pm_comm_read_byte(slave_id, HAPTICS_REG_ADDR(status_data_lsb), &status_buf[1]);

       err_flag |= pm_sdam_mem_write(PMIC_A, PM_SDAM_46, SDAM_MEM_006, 2, status_buf);
    }

    /* Stop haptics */
    err_flag |= pm_comm_write_byte(slave_id, HAPTICS_REG_ADDR(spmi_play), 0x01);
	
	/* Enable auto resonance, set auto resonance delay to 1 cycle, and set error window to 25% */
    err_flag |= pm_comm_write_byte(slave_id, HAPTICS_REG_ADDR(autores_cfg), ((1<<7) | (2<<2) | (1 << 0)));   
    err_flag |= pm_comm_write_byte(slave_id, HAPTICS_REG_ADDR(drv_duty), 0xE6);   
  }
  return err_flag;
}

pm_err_flag_type pm_haptics_enable(uint32 pmic_chip, pm_on_off_type enable) 
{
  pm_err_flag_type err_flag = pm_haptics_cfg_play(pmic_chip, enable);
  return err_flag;
}

pm_err_flag_type pm_haptics_set_actuator_type(uint32 pmic_chip, pm_haptics_actuator_type actuator_type)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  return err_flag;
}


pm_err_flag_type pm_haptics_wf_sel(uint32 pmic_chip, pm_haptics_wf_source_type wf_source_type, pm_haptics_wf_trigger_type wf_trigger_type)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  return err_flag;
}


pm_err_flag_type pm_haptics_fill_wf_buff(uint32 pmic_chip, pm_haptics_sample *wf_arry, size_t length)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  return err_flag;
}


pm_err_flag_type pm_haptics_set_lra_resonance_type(uint32 pmic_chip, pm_haptics_lra_res_type lra_res)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  return err_flag;
}


pm_err_flag_type pm_haptics_set_slew_rate(uint32 pmic_chip, pm_haptics_slew_rate slew_rate)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  return err_flag;
}


pm_err_flag_type pm_haptics_play(uint32 pmic_chip, pm_haptics_vibrate_type vibrate)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  return err_flag;
}


pm_err_flag_type pm_haptics_set_vmax_volt(uint32 pmic_chip, uint32 vmax_cfg_volt)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  pm_register_address_type reg_haptics_set_vmax = 0;
  pm_register_address_type reg_haptics_vmax_hdrm = 0;
  pm_haptics_data_type *haptics_ptr = pm_haptics_get_data(pmic_chip);
  pm_register_data_type data = 0;

  if (haptics_ptr == NULL) {
    return PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
  }

  if (vmax_cfg_volt > PM_HAPTICS_VMAX_VOLT_HIGH || vmax_cfg_volt < PM_HAPTICS_VMAX_VOLT_LOW) {
    return PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
  } else {
    data = vmax_cfg_volt / PM_HAPTICS_VMAX_VOLT_FACTOR;
  }
  reg_haptics_set_vmax = haptics_ptr->base_address + haptics_ptr->haptics_reg_table->vmax_cfg;
  reg_haptics_vmax_hdrm = haptics_ptr->base_address + haptics_ptr->haptics_reg_table->vmax_hdrm;

  err_flag = pm_comm_write_byte(haptics_ptr->comm_ptr->slave_id, reg_haptics_set_vmax, data);

  err_flag |= pm_comm_write_byte(haptics_ptr->comm_ptr->slave_id, reg_haptics_vmax_hdrm, pm_haptics_vmax_hdrm);
  return err_flag;
}

pm_err_flag_type pm_haptics_internal_pwm_freq_sel(uint32 pmic_chip, uint32 freq_sel_data_in_khz)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  return err_flag;
}

pm_err_flag_type pm_haptics_external_pwm_freq_sel(uint32 pmic_chip, uint32 freq_sel_data_in_khz)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  return err_flag;
}

pm_err_flag_type pm_haptics_pwm_cap_sel(uint32 pmic_chip, pm_haptics_pwm_cap_sel_type cap_sel_data)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  return err_flag;

}

pm_err_flag_type pm_haptics_wf_repeat(uint32 pmic_chip, pm_haptics_waveform_repeat_type wf_repeat_data, pm_haptics_waveform_s_repeat_type wf_s_repeat_data)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  return err_flag;
}

pm_err_flag_type pm_haptics_config_haptics_rate(uint32 pmic_chip, uint32 config_rate_in_us)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  return err_flag;
}

pm_err_flag_type pm_haptics_auto_res_cfg(uint32  pmic_chip, pm_haptics_lra_res_calib_type calib_period, 
                                         boolean calib_eop, pm_haptics_lra_high_z_type qwd_drive_duration, 
                                         uint32 cal_duration, pm_haptics_lra_auto_res_mode_type auto_res_mode
                                         )
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  return err_flag;
}

pm_err_flag_type pm_haptics_get_status(uint32 pmic_chip, pm_haptics_status *haptics_status)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  pm_haptics_data_type *haptics_ptr = pm_haptics_get_data(pmic_chip);

  pm_register_data_type data = 0;
  pm_register_address_type status_reg;

  if (haptics_ptr == NULL) {
    return PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
  }
  else if (haptics_status == NULL) {
    return PM_ERR_FLAG_INVALID_PARAMETER;;
  }
  else {
    status_reg = haptics_ptr->base_address + haptics_ptr->haptics_reg_table->fault_status;
    err_flag |= pm_comm_read_byte(haptics_ptr->comm_ptr->slave_id, status_reg, &data);

    haptics_status->sc_flag        = (data & 0x04) ? TRUE : FALSE;
    haptics_status->auto_res_err   = (data & 0x02) ? TRUE : FALSE;
  }

  return err_flag;
}


pm_err_flag_type pm_haptics_get_rate(uint32 pmic_chip, pm_haptics_rate_type rate_type, uint32 *rate)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  *rate = 0;
  return err_flag;
}
