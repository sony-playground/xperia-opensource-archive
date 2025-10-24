/*! \file
*
*  \brief  pm_pwm.c ---PWM Driver implementation.
*  \details PWM Driver implementation.
*  &copy; Copyright (c) 2012-2020, 2022 Qualcomm Technologies, Inc.  All Rights Reserved.
          Qualcomm Technologies Proprietary and Confidential.
*/

/*===========================================================================

EDIT HISTORY FOR MODULE



$Header: //components/rel/core.boot/6.1.1/QcomPkg/Library/PmicLib/drivers/pwm/src/pm_pwm.c#1 $
$Author: pwbldsvc $
$DateTime: 2022/08/18 10:15:46 $
when        who     what, where, why
--------    ---     ----------------------------------------------------------
08/20/14    al      Updating comm lib
05/20/14    al      Architecture update
10/16/12    al      added LUT support
07/23/12    al      Created.

===========================================================================*/

/*===========================================================================

INCLUDE FILES

===========================================================================*/
#include "pm_pwm.h"
#include "pm_pwm_driver.h"

/*===========================================================================

DEFINITIONS AND ENUMS

============================================================================*/
#define PWM_INVALID_BIT_SIZE               0xFF
#define PWM_MAX_SUPPORTED_BIT_SIZES_REV_B   2
#define PWM_MAX_SUPPORTED_BIT_SIZES_REV_C   8

uint8 pwm_size_value_map_rev_b[PM_PWM_SIZE__MAX + 1] = {
	[PM_PWM_SIZE__6BIT]   = 0,
	[PM_PWM_SIZE__7BIT]   = PWM_INVALID_BIT_SIZE,
	[PM_PWM_SIZE__8BIT]   = PWM_INVALID_BIT_SIZE,
	[PM_PWM_SIZE__9BIT]   = 1,
	[PM_PWM_SIZE__10BIT]  = PWM_INVALID_BIT_SIZE,
	[PM_PWM_SIZE__11BIT]  = PWM_INVALID_BIT_SIZE,
	[PM_PWM_SIZE__12BIT]  = PWM_INVALID_BIT_SIZE,
	[PM_PWM_SIZE__13BIT]  = PWM_INVALID_BIT_SIZE,
	[PM_PWM_SIZE__14BIT]  = PWM_INVALID_BIT_SIZE,
	[PM_PWM_SIZE__15BIT]  = PWM_INVALID_BIT_SIZE,
	[PM_PWM_SIZE__MAX]    = 1
};

uint8 pwm_size_value_map_rev_c[PM_PWM_SIZE__MAX + 1] = {
  [PM_PWM_SIZE__6BIT]   = PWM_INVALID_BIT_SIZE,
  [PM_PWM_SIZE__7BIT]   = PWM_INVALID_BIT_SIZE,
  [PM_PWM_SIZE__8BIT]   = 0,
  [PM_PWM_SIZE__9BIT]   = 1,
  [PM_PWM_SIZE__10BIT]  = 2,
  [PM_PWM_SIZE__11BIT]  = 3,
  [PM_PWM_SIZE__12BIT]  = 4,
  [PM_PWM_SIZE__13BIT]  = 5,
  [PM_PWM_SIZE__14BIT]  = 6,
  [PM_PWM_SIZE__15BIT]  = 7,
  [PM_PWM_SIZE__MAX]    = 7
};

uint8 pwm_value_size_map_rev_b[PWM_MAX_SUPPORTED_BIT_SIZES_REV_B] = {
  PM_PWM_SIZE__6BIT,
  PM_PWM_SIZE__9BIT
};

uint8 pwm_value_size_map_rev_c[PWM_MAX_SUPPORTED_BIT_SIZES_REV_C] = { 
  PM_PWM_SIZE__8BIT,
  PM_PWM_SIZE__9BIT,
  PM_PWM_SIZE__10BIT,
  PM_PWM_SIZE__11BIT,
  PM_PWM_SIZE__12BIT,
  PM_PWM_SIZE__13BIT,
  PM_PWM_SIZE__14BIT,
  PM_PWM_SIZE__15BIT
};

/*************************************
NOTE: VIRTUAL METHOD IMPLEMENTATION
**************************************/

#define ADDRESS(pwm_ptr, pwm_rsrc, offset)  ((pwm_ptr->base_address) + (pwm_rsrc * 0x100) + (pwm_ptr->pwm_reg_table->offset))
#define SLAVE_ID                            (pwm_ptr->comm_ptr->slave_id)

pm_err_flag_type
pm_pwm_enable_pwm (uint32 pmic_chip, pm_pwm_resource_type pwm_rsrc, boolean enable)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  pm_register_data_type data = 0x00;

  pm_pwm_data_type *pwm_ptr = pm_pwm_get_data(pmic_chip);
  if (pwm_ptr == NULL)
  {
    err_flag = PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
  }
  else if (pwm_rsrc >= pwm_ptr->num_of_peripherals)
  {
    err_flag = PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
  }
  else
  {
    pm_register_address_type enable_control = ADDRESS(pwm_ptr, pwm_rsrc, enable_control);
    data = (enable)? 0x80 : 0x00;
    err_flag = pm_comm_write_byte_mask(SLAVE_ID, enable_control, 0x80, data);
  }

  return err_flag;
}

pm_err_flag_type
pm_pwm_set_pwm_value (uint32 pmic_chip, pm_pwm_resource_type pwm_rsrc, uint16 pwm_value)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;

  pm_pwm_data_type *pwm_ptr = pm_pwm_get_data(pmic_chip);

  if (pwm_ptr == NULL)
  {
    err_flag = PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
  }
  else if (pwm_rsrc >= pwm_ptr->num_of_peripherals)
  {
    err_flag = PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
  }
  else
  {
    pm_register_address_type pwm_value_lsb = ADDRESS(pwm_ptr, pwm_rsrc, pwm_value_lsb);
    pm_register_address_type pwm_value_msb = ADDRESS(pwm_ptr, pwm_rsrc, pwm_value_msb);
    pm_register_address_type pwm_sync = ADDRESS(pwm_ptr, pwm_rsrc, pwm_sync);

    pwm_value = (pwm_value > (pwm_ptr->pwm_specific_data->max_pwm_value)) ? (pwm_ptr->pwm_specific_data->max_pwm_value) : 
                                                                             pwm_value;

    err_flag = pm_comm_write_byte(SLAVE_ID, pwm_value_lsb, (pm_register_data_type)(pwm_value & 0xFF));
    err_flag |= pm_comm_write_byte(SLAVE_ID, pwm_value_msb, (pm_register_data_type)(pwm_value>>8));
    //Writing 1 to pwm_sync register will update the PWM value. This bit is auto-cleared
    err_flag |= pm_comm_write_byte_mask(SLAVE_ID, pwm_sync, 0x01,(pm_register_data_type)0x01);
  }

  return err_flag;
}

pm_err_flag_type
pm_pwm_clock_config(uint32 pmic_chip, pm_pwm_resource_type pwm_rsrc, pm_pwm_bit_size_type bit_size,  pm_pwm_clock_freq_type clk_freq, uint32 pre_div, uint32 exp )
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  uint8 bit_shift = 0;
  uint8 bit_size_value = 0;

  pm_pwm_data_type *pwm_ptr = pm_pwm_get_data(pmic_chip);

  if (pwm_ptr == NULL)
  {
    err_flag = PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
  }
  else if (pwm_rsrc >= pwm_ptr->num_of_peripherals)
  {
    err_flag = PM_ERR_FLAG_INVALID_PARAMETER;
  }
  else if((bit_size > (pwm_ptr->pwm_specific_data->max_pwm_size)) && (bit_size != PM_PWM_SIZE__MAX)) 
  {
    err_flag = PM_ERR_FLAG_INVALID_PARAMETER;
  }
  else if((clk_freq > (pwm_ptr->pwm_specific_data->max_freq)) || 
          (clk_freq == PM_PWM_CLK__38_4_MHZ)) 
  //Existing hardware doesn't support 38.4MHz frquency but subsequent revisions might contain.
  {
    err_flag = PM_ERR_FLAG_INVALID_PARAMETER;
  }
  else if(pre_div > 6)
  {
    err_flag = PM_ERR_FLAG_INVALID_PARAMETER;
  }
  else if(exp >= 8)
  {
    err_flag = PM_ERR_FLAG_INVALID_PARAMETER;
  }
  else
  {
    pm_register_address_type pwm_size_clk = ADDRESS(pwm_ptr, pwm_rsrc, pwm_size_clk);
    pm_register_address_type pwm_freq_prediv_clk = ADDRESS(pwm_ptr, pwm_rsrc, pwm_freq_prediv_clk);
    bit_size_value = (pwm_ptr->periph_subtype == PERIPH_SUBTYPE_PWM_REV_C) ? 
                            pwm_size_value_map_rev_c[bit_size] : pwm_size_value_map_rev_b[bit_size];
    
    if(bit_size_value == PWM_INVALID_BIT_SIZE)
    {
      return PM_ERR_FLAG_INVALID_PARAMETER;
    }

    pre_div = pre_div/2; //0 = PRE_DIV__1, 1 = PRE_DIV__3, 2 = PRE_DIV__5, 3 = PRE_DIV__6
    bit_shift = pwm_ptr->pwm_specific_data->pwm_size_start_bit_pos;
	
	
	  // Mapping CLK_FREQ enum value to register
    if (clk_freq == PM_PWM_CLK__76_8_MHZ)
	  {
		  clk_freq -= 1;
	  }
	
    err_flag = pm_comm_write_byte_mask( SLAVE_ID, 
                                        pwm_size_clk, 
                                        (pwm_ptr->pwm_specific_data->size_mask | pwm_ptr->pwm_specific_data->clk_mask), 
                                        (pm_register_data_type)((bit_size_value << bit_shift)|clk_freq));

    err_flag |= pm_comm_write_byte_mask(SLAVE_ID, 
                                        pwm_freq_prediv_clk, 
                                        0x67,
                                        (pm_register_data_type)((pre_div<<5)|exp));
  }
  return err_flag;
}

pm_err_flag_type
pm_pwm_glitch_removal(uint32 pmic_chip, pm_pwm_resource_type pwm_rsrc, boolean glitch_removal )
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  pm_register_data_type data = 0x00;

  pm_pwm_data_type *pwm_ptr = pm_pwm_get_data(pmic_chip);

  if (pwm_ptr == NULL)
  {
    err_flag = PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
  }
  else if (pwm_rsrc >= pwm_ptr->num_of_peripherals)
  {
    err_flag = PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
  }
  else
  {
    pm_register_address_type pwm_type_config = ADDRESS(pwm_ptr, pwm_rsrc, pwm_type_config);

    data = (glitch_removal) ? 0xFF : 0x00;

    err_flag = pm_comm_write_byte_mask(SLAVE_ID, pwm_type_config, 0x20, data);
  }

  return err_flag;
}


pm_err_flag_type
pm_pwm_get_status (uint32 pmic_chip, pm_pwm_resource_type pwm_rsrc, pm_pwm_status_type *pwm_status)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  pm_register_data_type data = 0;
  uint8 clk_mask = 0, size_mask = 0, bit_shift = 0, pwm_value_msb_mask = 0;

  pm_pwm_data_type *pwm_ptr = pm_pwm_get_data(pmic_chip);
  
  if (pwm_ptr == NULL)
  {
    return PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
  }
  else if (pwm_rsrc >= pwm_ptr->num_of_peripherals)
  {
    err_flag = PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
  }
  else
  {
    pm_register_address_type pwm_size_clk = ADDRESS(pwm_ptr, pwm_rsrc, pwm_size_clk);
    pm_register_address_type pwm_freq_prediv_clk = ADDRESS(pwm_ptr, pwm_rsrc, pwm_freq_prediv_clk);
    pm_register_address_type pwm_type_config = ADDRESS(pwm_ptr, pwm_rsrc, pwm_type_config);
    pm_register_address_type pwm_value_lsb = ADDRESS(pwm_ptr, pwm_rsrc, pwm_value_lsb);
    pm_register_address_type pwm_value_msb = ADDRESS(pwm_ptr, pwm_rsrc, pwm_value_msb);
    pm_register_address_type enable_control = ADDRESS(pwm_ptr, pwm_rsrc, enable_control);

    /*Get PWM enable status*/
    err_flag =  pm_comm_read_byte_mask(SLAVE_ID, enable_control, 0x80, &data);
    pwm_status->pwm_enable = (data&0x80)?TRUE:FALSE;
    
    /*Get PWM LSB and MSB value*/
    err_flag |=  pm_comm_read_byte_mask(SLAVE_ID, pwm_value_lsb, 0xFF, &data);
    pwm_status->pwm_value = data; //writing LSB for duty cycle

    pwm_value_msb_mask = (pwm_ptr->pwm_specific_data->max_pwm_value >> 8);
    err_flag |= pm_comm_read_byte_mask(SLAVE_ID, pwm_value_msb, pwm_value_msb_mask, &data);
    pwm_status->pwm_value |= (data<<8); //MSB for duty cycle

    /*Get CLK frequency setting*/
    clk_mask = pwm_ptr->pwm_specific_data->clk_mask;
	  err_flag |=  pm_comm_read_byte_mask(SLAVE_ID, pwm_size_clk, clk_mask, &data);
	  pwm_status->clk_freq = data;
    if(pwm_status->clk_freq == PM_PWM_CLK__38_4_MHZ)
    {
      /*Value 4 represents PM_PWM_CLK__76_8_MHZ and not PM_PWM_CLK__38_4_MHZ, adjusting to appropriate enum entry.*/
      pwm_status->clk_freq = PM_PWM_CLK__76_8_MHZ;
    }
	
	  /*Get PWM size setting*/
	  size_mask = pwm_ptr->pwm_specific_data->size_mask;
	  bit_shift = pwm_ptr->pwm_specific_data->pwm_size_start_bit_pos;
	  err_flag |=  pm_comm_read_byte_mask(SLAVE_ID, pwm_size_clk, size_mask, &data);
    data = (data >> bit_shift);
    /*Adjusting the bit_size to appropriate enum. */
    pwm_status->bit_size = (pwm_ptr->periph_subtype == PERIPH_SUBTYPE_PWM_REV_C) ? 
                            pwm_value_size_map_rev_c[data] : pwm_value_size_map_rev_b[data];
	
  	/*Get pre_div and exponent setting*/
  	err_flag |= pm_comm_read_byte_mask(SLAVE_ID, pwm_freq_prediv_clk, 0x67, &data);
  	pwm_status->exp = (data&0x07);
  	if(((data&0x60)>>5)==3)
  	{
  	  pwm_status->pre_div = ((data&0x60)>>5) *2;
  	}
  	else
  	{
  	  pwm_status->pre_div = (((data&0x60)>>5) *2) + 1;
  	}

  	/*Get PWM glitch removal status*/
  	err_flag |=  pm_comm_read_byte_mask(SLAVE_ID, pwm_type_config, 0x20, &data);
  	pwm_status->glitch_removal=(data)?TRUE:FALSE;
  }
    
  return err_flag;
}
